#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"
#include "color.h"
/**
 * \file color.c
 * \author Team BMC editor 
 */


/**
 * default syntax colors
 */
static GdkColor note_color;
static GdkColor bar_color;




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
    
    init_colors();
    
    if(clik%2 == 0)
	color_barline(editor);
    else
        syntax_highlighting_off(editor);
	clik ++;

}

void init_colors() {
    static int initialised = 0;
    if(!initialised) {
	gdk_color_parse("green", &bar_color);
	initialised = 1;
    }
}

void set_tags(GtkTextBuffer *buffer) {
    GtkTextIter start, end;
    GtkTextTagTable *tag_table = gtk_text_buffer_get_tag_table(buffer);
    
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    GtkTextTag *tag = gtk_text_tag_table_lookup(tag_table,"bar");
    if(tag) {
	//gtk_text_buffer_remove_tag_by_name(buffer, "bar", 
	//&start, &end);
	gtk_text_tag_table_remove(tag_table, tag);
	    
	    }
    gtk_text_buffer_create_tag(buffer, "bar", "foreground", 
			       gdk_color_to_string(&bar_color), NULL); 
    
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
    GtkTextIter start, end;
    GtkTextIter start_match, end_match;

    gchar bar_line[4] ={0xE2,0xA0,0x87,0x0};
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    gtk_text_buffer_get_start_iter(buffer, &start_match);
    gtk_text_buffer_get_start_iter(buffer, &end_match);
    
    set_tags(buffer);

    
    do {
	gtk_text_iter_forward_chars(&end_match, 1);
	gchar *c = gtk_text_iter_get_slice(&start_match, &end_match);
	//g_fprintf(stderr, "%s\n",c);
	if(g_strcmp0(bar_line, c) == 0)
	    gtk_text_buffer_apply_tag_by_name(buffer, "bar", &start_match, &end_match);
		
    } while(gtk_text_iter_forward_chars(&start_match, 1));
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

/*This function will propose the different types of data (note, pause, measure bar, ...) that can be colored as the user wants
 */
void color_options(GtkWidget *widget, BrailleMusicEditor *editor) {
    GtkWidget* dialog;
    
    // Creation of a dialog window
    dialog = gtk_dialog_new_with_buttons("Syntax Highlighting",
 					 GTK_WINDOW(editor->window),
					 GTK_DIALOG_MODAL,
					 GTK_STOCK_CANCEL,
					 GTK_RESPONSE_CANCEL,
					 GTK_STOCK_OK,
					 GTK_RESPONSE_OK,
					 NULL);  

    gtk_window_set_default_size(GTK_WINDOW(dialog), 220, -1);
			    
    /*type 1 : note
    type 2 : measure bar
    type 3 : key
    type 4 : repetition
    */
    //const gchar* note_label = "Note";
    //const gchar* bar_label = "Bar";
  
    GtkWidget *note = gtk_button_new_with_label("Note");
    GtkWidget *bar = gtk_button_new_with_label("Bar");

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), note,
		       TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), bar ,
		       TRUE, TRUE, 0);
  
    g_signal_connect(G_OBJECT(note),"clicked", 
		     G_CALLBACK(color_selection), editor);
    g_signal_connect(G_OBJECT(bar),"clicked",
		     G_CALLBACK(color_selection),editor);

    gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);

    init_colors();

    gtk_widget_modify_bg(bar, GTK_STATE_NORMAL, &bar_color);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    GtkStyle *style;

    // run the dialog window
    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	    style = gtk_widget_get_style(bar);
	    bar_color = style->bg[GTK_STATE_NORMAL];
	    set_tags(buffer);
	    syntax_highlighting(widget, editor);
	    syntax_highlighting(widget, editor);
	    break;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
	    break;
	}
 
    // Destruction of the dialog window
    gtk_widget_destroy((GtkWidget *) dialog); 
 
  

}
void color_selection(GtkWidget *widget, BrailleMusicEditor *editor)
{

    GtkResponseType result;
    GtkColorSelection *colorsel;
    GtkWidget *dialog = gtk_color_selection_dialog_new("Font Color");
  
    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK)
	{
	    GdkColor color;
	    colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel);
	    gtk_color_selection_get_current_color(colorsel, &color);
	    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
	} 

    gtk_widget_destroy(dialog);
}
