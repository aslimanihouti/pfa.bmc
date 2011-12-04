#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"

void new_file(GtkWidget * widget, BrailleMusicEditor *editor)
{
	GtkTextBuffer *buffer;
	
	editor->filename = NULL;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor->textview));
	gtk_text_buffer_set_text (buffer, "", -1);
	gtk_text_buffer_set_modified (buffer, FALSE);
	
}
