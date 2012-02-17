#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"
#include "color.h"
/**
 * \file color.c
 * \author Team BMC editor 
 */

/**
 * \fn void syntax_highlighting(GtkButton *widget, BrailleMusicEditor *editor)
 * \brief This function enable/disable the syntax highlighting.
 * \param widget The button trigerring the function.
 * \param editor The structure holding the data.
 * 
 *
 */
void syntax_highlighting(GtkButton *widget, BrailleMusicEditor *editor)
{	
    static int clik=0;
    
    
    if(clik%2 == 0)
	color_barline(editor);
    else
        syntax_highlighting_off(editor);
	clik ++;

}


/**
 * \fn void color_barline(BrailleMusicEditor *editor)
 * \brief This function color the barlines in the textview.
 * \param editor The structure holding the data.
 * 
 * This function will color the barline present in text in blue. 
 */

void color_barline(BrailleMusicEditor *editor)
{
    GtkTextIter start_find, end_find;
    GtkTextIter start_match, end_match;

    gchar bar_line[4] ={0xE2,0xA0,0x87,0x0};
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    gtk_text_buffer_create_tag(buffer, "blue_fg", 
			       "foreground", "blue", NULL); 
    
    gtk_text_buffer_get_start_iter(buffer, &start_find);
    gtk_text_buffer_get_end_iter(buffer, &end_find);
    
    gtk_text_buffer_remove_tag_by_name(buffer, "blue_fg", 
				       &start_find, &end_find);  
    
    
    while ( gtk_text_iter_forward_search(&start_find, bar_line, 
					 GTK_TEXT_SEARCH_TEXT_ONLY | 
					 GTK_TEXT_SEARCH_VISIBLE_ONLY, 
					 &start_match, &end_match, NULL) ) {
	
	gtk_text_buffer_apply_tag_by_name(buffer, "blue_fg", &start_match, &end_match);
	gtk_text_buffer_place_cursor(buffer, &start_match); 
	int offset = gtk_text_iter_get_offset(&end_match);
	gtk_text_buffer_get_iter_at_offset(buffer, &start_find, offset);
    }
}


/**
 * \fn void syntax_highlighting_off(BrailleMusicEditor *editor)
 * \brief This function removes the syntax highlighting.
 * \param editor The structure holding the data.
 *  
 */


void syntax_highlighting_off(BrailleMusicEditor *editor) 
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
}
