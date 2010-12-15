/*
 * Copyright (C) 2010 Vivien Barousse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define PURPLE_PLUGINS

#define PLUGIN_ID "core-viv-rdchooser"

#include <time.h>
#include <string.h>

#include <glib.h>

#include <libpurple/cmds.h>
#include <libpurple/notify.h>
#include <libpurple/plugin.h>
#include <libpurple/version.h>


static PurplePlugin* plugin;
    
static PurpleCmdRet choose_callback(PurpleConversation* conv,
        const gchar* cmd, 
        gchar** args,
        gchar** error,
        void* data) {
    
    char* options = strdup(args[0]);

    // Way to big, but isn't used for much time...
    char** tokens = malloc(sizeof(char*) * strlen(options));

    char* token = strtok(options, ",");
    int i = 0;
    do {
        tokens[i] = token;
        i++;
    } while ((token =/*=*/ strtok(NULL, ",")) != NULL);
    tokens[i] = NULL;

    int rdIdx = rand() % i;
    int firstNonspace = 0;
    while ((tokens[rdIdx] + firstNonspace)[0] == ' ') {
        firstNonspace += 1;
    }

    char* strippedChoice = tokens[rdIdx] + firstNonspace;

    char* pattern = "Options were: %s. Choice is: %s.";
    int patternLength = strlen(pattern) + strlen(strippedChoice) + strlen(args[0]);
    char* msg = malloc(sizeof(char) * (patternLength + 1));
    sprintf(msg, pattern, args[0], strippedChoice);

    purple_conv_im_send(PURPLE_CONV_IM(conv), msg);

    free(tokens);
    free(msg);
    free(options);

    return PURPLE_CMD_RET_OK;

}

static PurpleCmdId choose_command;

static gboolean plugin_load(PurplePlugin* plg) {
    plugin = plg;

    choose_command = purple_cmd_register("choose",
            "s",
            PURPLE_CMD_P_DEFAULT,
            PURPLE_CMD_FLAG_IM,
            PLUGIN_ID,
            choose_callback,
            "Choose randomply between multiple options",
            NULL);

    return TRUE;
}

static gboolean plugin_unload(PurplePlugin* plugin) {
    purple_cmd_unregister(choose_command);

    return TRUE;
}


static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    PLUGIN_ID,
    "Random chooser",
    "1.0",

    "Random chooser plugin",          
    "Random chooser plugin",          
    "Vivien Barousse <barousse.vivien@gmail.com>",                          
    "http://blog.aperigeek.com/viv/",     
    
    plugin_load,                   
    plugin_unload,                          
    NULL,                          
                                   
    NULL,                          
    NULL,                          
    NULL,                        
    NULL,                   
    NULL,                          
    NULL,                          
    NULL,                          
    NULL                           
};                               

static void init_plugin(PurplePlugin *plg) {
}

PURPLE_INIT_PLUGIN(hello_world, init_plugin, info)
