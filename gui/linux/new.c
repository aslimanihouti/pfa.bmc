#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"
#include "new.h"

/**
 * \file new.c
 * \author Team BMC editor 
 */

/**
 * \fn void new_file(GtkWidget * widget, BrailleMusicEditor *editor)
 * \brief The function called when selecting new file.
 * \param widget The object trigerring the function, in this case, the button save file.
 * \param editor The structure holding the data.

 * The function will check and see if there is data on the editor and ask the user to save or not by calling check_for_save.
 */

void new_file(GtkWidget * widget, BrailleMusicEditor *editor)
{
	gint resp=check_for_save (editor);
	if (resp == 1)
		{
			save_file(widget, editor);
			new_file_(editor);
		}			
	else if(resp == 0)
		new_file_(editor);
  
}


/** 
 * \fn void new_file_(BrailleMusicEditor *editor)
 * \brief This function actually opens a new file.
 * \param editor The structure holding the data.
 */
void new_file_(BrailleMusicEditor *editor)
{
	GtkTextBuffer *buffer;
	
	editor->filename = NULL;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor->textview));
	gtk_text_buffer_set_text (buffer, "", -1);
	gtk_text_buffer_set_modified (buffer, FALSE);	
}
