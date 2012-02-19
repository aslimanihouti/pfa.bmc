#include <gtk/gtk.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "BrailleMusicEditor.h"


void compile(GtkWidget *widget, BrailleMusicEditor *editor)
{
    GPid pid;
    GtkTextBuffer *buffer;
    char *argv[2];
    gchar cmd[] = "./bmc";
    int standard_output, standard_error; 
    gchar buf[1024];
    gint chars_read = 1024;
    GtkTextIter iter;
    int fd;
    
    fd = open(editor->filename, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    argv[0]=cmd;
    argv[1]=NULL;
    g_spawn_async_with_pipes( "../../bmc", // const gchar *working_directory
    			      argv,    // gchar **argv
    			      NULL,       // gchar **envp
    			      G_SPAWN_SEARCH_PATH | G_SPAWN_CHILD_INHERITS_STDIN ,       // GSpawnFlags flags
    			      NULL,       // GSpawnChildSetupFunc child_setup
    			      NULL,       // gpointer user_data
    			      &pid,       // GPid *child_pid
    			      NULL,       // gint *standard_input
    			      &standard_output,   // gint *standard_output
    			      &standard_error,       // gint *standard_error
    			      NULL);    // GError **error


    buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->error_view));
    gtk_text_buffer_get_end_iter(buffer, &iter);
    
    while (chars_read > 0){
	chars_read = read(standard_error, buf, 1024);
	gtk_text_buffer_insert (buffer, &iter, buf, chars_read);
	
    }
    close(fd);
    close(standard_error);
    close(standard_output);
}
