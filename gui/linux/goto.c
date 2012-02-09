#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "BrailleMusicEditor.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
static gchar bar_line[4];   

void load_braille_char() 
{
    static int loaded =0;
    if(!loaded) {
	int fd = open("bar_line",O_RDONLY);
	read(fd,bar_line,4);
	close(fd);
	loaded = 1;
    }
}

void goto_next_prev(GtkWidget * widget, BrailleMusicEditor *editor, char n_p) 
{
    GtkTextIter start_find, end_find;
    GtkTextIter start_match, end_match;
    GtkTextMark *cursor;
    GtkTextBuffer * buffer; 
    
    load_braille_char();
    
    // Get the textview buffer. 
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview));
    // Get the mark at cursor. 
    cursor = gtk_text_buffer_get_mark (buffer, "insert");
    // Get the iter at cursor. 
    gtk_text_buffer_get_iter_at_mark (buffer, &start_find, cursor);
    
    gtk_text_buffer_get_end_iter(buffer, &end_find);
    
    gboolean go;
    if(n_p == 'n')
	go = gtk_text_iter_forward_search(&start_find, bar_line, 
					    GTK_TEXT_SEARCH_TEXT_ONLY | 
					    GTK_TEXT_SEARCH_VISIBLE_ONLY, 
					    &start_match, &end_match, NULL);
    else if(n_p == 'p') {
	gtk_text_iter_backward_cursor_position(&start_find);
	go = gtk_text_iter_backward_search(&start_find, bar_line, 
					   GTK_TEXT_SEARCH_TEXT_ONLY | 
					   GTK_TEXT_SEARCH_VISIBLE_ONLY, 
					   &start_match, &end_match, NULL);
    }
    if (go) {
	gtk_text_buffer_place_cursor(buffer, &end_match); 
	int offset = gtk_text_iter_get_offset(&end_match);
	gtk_text_buffer_get_iter_at_offset(buffer, &start_find, offset);
    }
}

void goto_next(GtkWidget * widget, BrailleMusicEditor *editor) 
{
    goto_next_prev(widget, editor, 'n');
}

void goto_prev(GtkWidget * widget, BrailleMusicEditor *editor) 
{
    goto_next_prev(widget, editor, 'p');
}
