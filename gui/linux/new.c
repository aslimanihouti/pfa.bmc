#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"
#include "new.h"

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



void new_file_(BrailleMusicEditor *editor)
{
	GtkTextBuffer *buffer;
	
	editor->filename = NULL;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor->textview));
	gtk_text_buffer_set_text (buffer, "", -1);
	gtk_text_buffer_set_modified (buffer, FALSE);	
}
