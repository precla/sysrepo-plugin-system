#include <system.h>
#include <common.h>
#include <context.h>
#include <utils/memory.h>

// stdlib
#include <stdbool.h>

// sysrepo
#include <sysrepo.h>

// libyang
#include <libyang/tree_data.h>

// bridging
#include "startup.h"

// check if the datastore which the session uses is empty (startup or running)
static bool bridging_datastore_is_empty(sr_session_ctx_t *session);

int sr_plugin_init_cb(sr_session_ctx_t *running_session, void **private_data)
{
	int error = 0;

	// sysrepo
	sr_session_ctx_t *startup_session = NULL;
	sr_conn_ctx_t *connection = NULL;
	sr_subscription_ctx_t *subscription = NULL;

	// plugin
	system_ctx_t *ctx = NULL;

	// init context
	ctx = xmalloc(sizeof(*ctx));
	*ctx = (system_ctx_t){0};

	*private_data = ctx;

	connection = sr_session_get_connection(running_session);
	error = sr_session_start(connection, SR_DS_STARTUP, &startup_session);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_session_start() error (%d): %s", error, sr_strerror(error));
		goto error_out;
	}

	ctx->startup_session = startup_session;

	if (bridging_datastore_is_empty(startup_session)) {
		SRPLG_LOG_INF(PLUGIN_NAME, "Startup datasore is empty");
		SRPLG_LOG_INF(PLUGIN_NAME, "Loading initial system data");
		// error = system_startup_load_data(ctx, startup_session);
		// if (error) {
		// 	SRPLG_LOG_ERR(PLUGIN_NAME, "Error loading initial data into the startup datastore... exiting");
		// 	goto error_out;
		// }

		// // copy contents of the startup session to the current running session
		// error = sr_copy_config(running_session, BASE_YANG_MODEL, SR_DS_STARTUP, 0);
		// if (error) {
		// 	SRPLG_LOG_ERR(PLUGIN_NAME, "sr_copy_config() error (%d): %s", error, sr_strerror(error));
		// 	goto error_out;
		// }
	}

	goto out;

error_out:
	error = -1;
	SRPLG_LOG_ERR(PLUGIN_NAME, "Error occured while initializing the plugin (%d)", error);

out:
	return error ? SR_ERR_CALLBACK_FAILED : SR_ERR_OK;
}

void sr_plugin_cleanup_cb(sr_session_ctx_t *running_session, void *private_data)
{
	int error = 0;

	system_ctx_t *ctx = (system_ctx_t *) private_data;

	// save current running configuration into startup for next time when the plugin starts
	error = sr_copy_config(ctx->startup_session, BASE_YANG_MODEL, SR_DS_RUNNING, 0);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_copy_config() error (%d): %s", error, sr_strerror(error));
	}

	FREE_SAFE(ctx);
}

static bool bridging_datastore_is_empty(sr_session_ctx_t *session)
{
	int error = SR_ERR_OK;
	bool is_empty = true;
	sr_data_t *test_data = NULL;

	error = sr_get_subtree(session, SYSTEM_SYSTEM_CONTAINER_YANG_PATH, 0, &test_data);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_get_subtree() error (%d): %s", error, sr_strerror(error));
		goto out;
	}

	if (test_data->tree != NULL && lyd_child(test_data->tree) != NULL) {
		// main container found: datastore is not empty
		is_empty = false;
	}

out:
	sr_release_data(test_data);

	return is_empty;
}