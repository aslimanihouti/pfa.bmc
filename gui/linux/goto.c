#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

gboolean key_pressed(GtkWidget * window, GdkEventKey* event, GtkTextBuffer *buffer) 
{
    GtkTextIter start_find, end_find;
    GtkTextIter start_match, end_match;
    GtkTextMark *cursor;
    gchar text[4];  
  
    int fd=open("bar_line",O_RDONLY);
    read(fd,text,4);
    close(fd);
    
    // Get the mark at cursor. 
    cursor = gtk_text_buffer_get_mark (buffer, "insert");
    // Get the iter at cursor. 
    gtk_text_buffer_get_iter_at_mark (buffer, &start_find, cursor);

    gtk_text_buffer_get_end_iter(buffer, &end_find);
		
    if ((event->type == GDK_KEY_PRESS) && 
	(event->state & GDK_CONTROL_MASK)) {

	switch (event->keyval)
	    {
	    case GDK_Left :
		gtk_text_buffer_remove_tag_by_name(buffer, "gray_bg", &start_find, &end_find);  
		  		    
		if ( gtk_text_iter_forward_search(&start_find, text, 
						  GTK_TEXT_SEARCH_TEXT_ONLY | GTK_TEXT_SEARCH_VISIBLE_ONLY, 
						  &start_match, &end_match, NULL) ) {
		    gtk_text_buffer_place_cursor(buffer, &end_match); 
		    int offset = gtk_text_iter_get_offset(&end_match);
		    gtk_text_buffer_get_iter_at_offset(buffer, 
						       &start_find, offset);
		}
		
		

		break;

	    case GDK_r:
		gtk_text_buffer_get_start_iter(buffer, &start_find);
		gtk_text_buffer_get_end_iter(buffer, &end_find);
      
		gtk_text_buffer_remove_tag_by_name(buffer, "gray_bg", 
						   &start_find, &end_find);  
		break;
	    }
    }
    
    return FALSE;
}

