#include <stdio.h>
#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"
#include "errors.h"
#include "open.h"
#include "save.h"
/**
 * \file open.c
 * \author Team BMC editor 
 */


/**
 * \fn void open_file(GtkWidget *widget, BrailleMusicEditor *editor)
 * \brief That function is called when selecting open file.
 *  \param widget The object that triggers the function, here, the button open file.
 * \param editor The structure holding the data.
 * 
 * This function will check if there is unsaved changes in the editor calling check_for_save function.
 */
void open_file(GtkWidget *widget, BrailleMusicEditor *editor)
{
    gint resp=check_for_save (editor);
    if (resp == 1){
	save_file(widget, editor);
	open_file_(editor);
    }			
    else if(resp == 0)
	open_file_(editor);
    editor->text_changed = FALSE;
}

/**
 * \fn void open_file_(BrailleMusicEditor *editor)
 * \brief This function actually opens a file
 * \param editor The structure holding the data.
 */
void open_file_(BrailleMusicEditor *editor)
{		
    GtkTextBuffer *buffer;
    GtkTextIter start;
    GtkTextIter end;
    GtkWidget * file_selection;
    FILE *file;
    gchar *path;
    gchar read[1024];

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview));

    //creation of the file selection window
    file_selection = gtk_file_chooser_dialog_new ("Open File", NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    
    //banning use of other window
    gtk_window_set_modal(GTK_WINDOW(file_selection), TRUE);
    if(gtk_dialog_run(GTK_DIALOG(file_selection))==GTK_RESPONSE_ACCEPT){
	/* retrival of the file path */
	path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selection));
	file = fopen(path,"r");
	open_error(file_selection, file, "Can't open the file : \n%s", path);
	
	//save the current file path
	editor->filename=path;

	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_delete(buffer, &start, &end);

	while(fgets(read, 1024, file)){
	    gtk_text_buffer_get_end_iter(buffer, &end);
	    gtk_text_buffer_insert(buffer, &end, read, -1);
	}
	fclose(file);
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_place_cursor(buffer, &start);
    }
    gtk_widget_destroy(file_selection); 
}
