#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"
#include "color.h"
#include <string.h>
/**
 * \file color.c
 * \author Team BMC editor 
 */


/**
 * default syntax colors
 */
#define NB_TYPES 17
static GdkColor color_table[NB_TYPES];

static char type_table[NB_TYPES][22] = {
    "Accidental",
    "Articulation",
    "Bar",
    "Clef",
    "Dot",
    "Fingering",
    "In_accord",
    "Intervals",
    "Note",
    "Octave",
    "Ornament",
    "Repetitons & Tremolo",
    "Rest",
    "Slur & Tie",
    "Stem",
    "Tuplet",
    "Right or Left hand"
};

static char default_color_table[NB_TYPES][8] = {
    "#FF0000",
    "#00FFDB",
    "#FF4C00",
    "#C7DE3E",
    "#719AB9",
    "#C38B02",
    "#5E5402",
    "#FFE827",
    "#0000FF",
    "#EB6397",
    "#00FF00",
    "#5D0000",
    "#72008B",
    "#A4A1A5",
    "#4DCD99",
    "#C02492",
    "#60754E",
};


static GHashTable *braille_table; 

static gchar accidentals[3][4] = {
    {0xE2,0xA0,0xA9,0x0}, //sharp
    {0xE2,0xA0,0xA3,0x0}, //flat
    {0xE2,0xA0,0xA1,0x0} //natural
};

static gchar articulations[13][7] = {
    {0xE2,0xA0,0xA6,0x0}, // a dot
    {0xE2,0xA0,0xA0,0xE2,0xA0,0xA6,0x0}, //a pear-shaped 
    {0xE2,0xA0,0x90,0xE2,0xA0,0xA6,0x0}, //a dot \a line 
    {0xE2,0xA0,0xB8,0xE2,0xA0,0xA6,0x0}, //a line 
    {0xE2,0xA0,0xA8,0xE2,0xA0,0xA6,0x0}, // >
    {0xE2,0xA0,0x88,0xE2,0xA0,0xA6,0x0}, // <
    {0xE2,0xA0,0xB0,0xE2,0xA0,0xA6,0x0}, // ^
    {0xE2,0xA0,0xA3,0xE2,0xA0,0x87,0x0}, // Fermata
    {0xE2,0xA0,0x9C,0xE2,0xA0,0x82,0x0}, // a comma
    {0xE2,0xA0,0x9C,0xE2,0xA0,0x85,0x0}, // A vertical wavy line or curve 
    {0xE2,0xA0,0xA1,0xE2,0xA0,0x84,0x0}, // <>
    {0xE2,0xA0,0x9C,0xE2,0xA0,0x89,0x0}, // Beginning of diverging lines
    {0xE2,0xA0,0x9C,0xE2,0xA0,0x92,0x0} // End of diverging lines   
};

//static gchar measure_bar[4] = {0xE2,0xA0,0x80,0x0};
static gchar ending_double_bar[7] = {0xE2,0xA0,0xA3,0xE2,0xA0,0x85,0x0};
static gchar sectional_double_bar[11] = {0xE2,0xA0,0xA3,0xE2,0xA0,0x85,0xE2,0xA0,0x84,0x0};

static gchar clefs[3][10] = {
    {0xE2,0xA0,0x9C,0xE2,0xA0,0x8C,0xE2,0xA0,0x87,0x0}, //G
    {0xE2,0xA0,0x9C,0xE2,0xA0,0xBC,0xE2,0xA0,0x87,0x0}, //F
    {0xE2,0xA0,0x9C,0xE2,0xA0,0xAC,0xE2,0xA0,0x87,0x0}  //C
};

static gchar dot[4] = {0xE2,0xA0,0x84,0x0};

static gchar fingerings[5][4] = {
    {0xE2,0xA0,0x81,0x0}, //1
    {0xE2,0xA0,0x83,0x0}, //2
    {0xE2,0xA0,0x87,0x0}, //3
    {0xE2,0xA0,0x82,0x0}, //4
    {0xE2,0xA0,0x85,0x0}, //5
};

static gchar in_accords[3][7] = {
    {0xE2,0xA0,0xA3,0xE2,0xA0,0x9C,0x0}, 
    {0xE2,0xA0,0x90,0xE2,0xA0,0x82,0x0},
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x85,0x0}
};

static gchar intervals[7][4] = {
    {0xE2,0xA0,0x8C,0x0}, //2nd
    {0xE2,0xA0,0xAC,0x0}, //3th
    {0xE2,0xA0,0xBC,0x0}, //4th
    {0xE2,0xA0,0x94,0x0}, //5th
    {0xE2,0xA0,0xB4,0x0}, //6th
    {0xE2,0xA0,0x92,0x0}, //7th
    {0xE2,0xA0,0xA4,0x0} //8th
};

static gchar notes[28][4] = {
    {0xE2,0xA0,0xBD,0x0}, //C
    {0xE2,0xA0,0xB5,0x0}, //D
    {0xE2,0xA0,0xAF,0x0}, //E
    {0xE2,0xA0,0xBF,0x0}, //F
    {0xE2,0xA0,0xB7,0x0}, //G
    {0xE2,0xA0,0xAE,0x0}, //A
    {0xE2,0xA0,0xBE,0x0}, //B

    {0xE2,0xA0,0x9D,0x0}, //C2(half)
    {0xE2,0xA0,0x95,0x0}, //D2
    {0xE2,0xA0,0x8F,0x0}, //E2
    {0xE2,0xA0,0x9F,0x0}, //F2
    {0xE2,0xA0,0x97,0x0}, //G2
    {0xE2,0xA0,0x8E,0x0}, //A2
    {0xE2,0xA0,0x9E,0x0}, //B2

    {0xE2,0xA0,0xB9,0x0}, //C4(quarter)
    {0xE2,0xA0,0xB1,0x0}, //D4
    {0xE2,0xA0,0xAB,0x0}, //E4
    {0xE2,0xA0,0xBB,0x0}, //F4
    {0xE2,0xA0,0xB3,0x0}, //G4
    {0xE2,0xA0,0xAA,0x0}, //A4
    {0xE2,0xA0,0xBA,0x0}, //B4

    {0xE2,0xA0,0x99,0x0}, //C8(eighth)
    {0xE2,0xA0,0x91,0x0}, //D8
    {0xE2,0xA0,0x8B,0x0}, //E8
    {0xE2,0xA0,0x9B,0x0}, //F8
    {0xE2,0xA0,0x93,0x0}, //G8
    {0xE2,0xA0,0x8A,0x0}, //A8
    {0xE2,0xA0,0x9A,0x0}, //B8
};

static gchar octaves[7][4] = {
    {0xE2,0xA0,0x88,0x0}, //1st
    {0xE2,0xA0,0x98,0x0}, //2nd
    {0xE2,0xA0,0xB8,0x0}, //3th
    {0xE2,0xA0,0x90,0x0}, //4th
    {0xE2,0xA0,0xA8,0x0}, //5th
    {0xE2,0xA0,0xB0,0x0}, //6th
    {0xE2,0xA0,0xA0,0x0} //7th
};

static gchar ornaments[9][7] = {
    {0xE2,0xA0,0xA2,0x0}, //Short appoggiatura 
    {0xE2,0xA0,0x90,0xE2,0xA0,0xA2,0x0}, //Long appoggiatura 
    {0xE2,0xA0,0x96,0x0}, //Trill
    {0xE2,0xA0,0xB2,0x0}, //Turn
    {0xE2,0xA0,0xA0,0xE2,0xA0,0xB2,0x0}, //Turn
    {0xE2,0xA0,0xB2,0xE2,0xA0,0x87,0x0}, //Turn
    {0xE2,0xA0,0x90,0xE2,0xA0,0x96,0x0}, // mordent
    {0xE2,0xA0,0xB0,0xE2,0xA0,0x96,0x0}, //Extented mordent
    {0xE2,0xA0,0x96,0xE2,0xA0,0x87,0x0} 
};

static gchar repetitons_tremolo[10][7] = {
    {0xE2,0xA0,0x98,0xE2,0xA0,0x83,0x0}, //8th
    {0xE2,0xA0,0x98,0xE2,0xA0,0x87,0x0}, //16th
    {0xE2,0xA0,0x98,0xE2,0xA0,0x82,0x0}, //32th
    {0xE2,0xA0,0x98,0xE2,0xA0,0x85,0x0}, //64th
    {0xE2,0xA0,0x98,0xE2,0xA0,0x84,0x0}, //128th
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x83,0x0}, //8th
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x87,0x0}, //16th
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x82,0x0}, //32th
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x81,0x0}, //64th
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x84,0x0} //128th
};

static gchar rests[4][4] = {
    {0xE2,0xA0,0x8D,0x0}, //rest 
    {0xE2,0xA0,0xA5,0x0}, //rest 2
    {0xE2,0xA0,0xA7,0x0}, //rest 4
    {0xE2,0xA0,0xAD,0x0}, //rest 8
};

static gchar slurs_ties[13][7] = {
    {0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0xB0,0xE2,0xA0,0x83,0x0},
    {0xE2,0xA0,0x98,0xE2,0xA0,0x86,0x0},
    {0xE2,0xA0,0xA0,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0x90,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0x88,0xE2,0xA0,0x87,0x0},
    {0xE2,0xA0,0x90,0xE2,0xA0,0x87,0x0},
    {0xE2,0xA0,0xB0,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0x88,0xE2,0xA0,0x86,0x0},
    {0xE2,0xA0,0x88,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0xA8,0xE2,0xA0,0x89,0x0},
    {0xE2,0xA0,0x98,0xE2,0xA0,0x89,0x0}
};

static gchar stems[6][7] = {
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x84,0x0}, //whole
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x85,0x0}, //half
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x81,0x0}, //quater
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x83,0x0}, //8th
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x87,0x0}, //16th
    {0xE2,0xA0,0xB8,0xE2,0xA0,0x82,0x0}, //32th
};

static gchar tuplet[6][7] = {
    {0xE2,0xA0,0xB0,0xE2,0xA0,0x82,0x0}, 
    {0xE2,0xA0,0x90,0xE2,0xA0,0x86,0x0}, 
    {0xE2,0xA0,0xB0,0xE2,0xA0,0x84,0x0}, 
    {0xE2,0xA0,0xA0,0xE2,0xA0,0x86,0x0}, 
    {0xE2,0xA0,0x90,0xE2,0xA0,0x84,0x0}, 
    {0xE2,0xA0,0xA0,0xE2,0xA0,0x82,0x0} 
};


static gchar right_hand[7] = {0xE2,0xA0,0xA8,0xE2,0xA0,0x9C,0x0};
static gchar left_hand[7] = {0xE2,0xA0,0xB8,0xE2,0xA0,0x9C,0x0};


static int coloration_enabled = 0;
/**
 * \fn void lexical_coloration(GtkButton *widget, BrailleMusicEditor *editor)
 * \brief This function enable/disable the syntax highlighting.
 * \param widget The button trigerring the function.
 * \param editor The structure holding the data.
 * 
 *
 */
void lexical_coloration(GtkWidget *widget, BrailleMusicEditor *editor)
{	
    
    
    init_colors();
    
    if(coloration_enabled%2 == 0)
	color(editor);
    else
        lexical_coloration_off(editor);
	coloration_enabled ++;
}

/*update th lexical coloration if it's enabled*/
void coloration_update(GtkWidget *widget, BrailleMusicEditor *editor)
{
    if(coloration_enabled%2 == 1)
	color(editor);    
}


/**
 * \fn void lexical_coloration_off(BrailleMusicEditor *editor)
 * \brief This function removes the syntax highlighting.
 * \param editor The structure holding the data.
 *  
 */
void lexical_coloration_off(BrailleMusicEditor *editor) 
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
}

void init_braille_table() {
    braille_table = g_hash_table_new(g_str_hash, g_str_equal);
    int i;
    for(i=0; i<3; i++) 
	g_hash_table_insert(braille_table, accidentals[i], type_table[0]);

    for(i=0; i<13; i++) 
	g_hash_table_insert(braille_table, articulations[i], type_table[1]);

    //g_hash_table_insert(braille_table, measure_bar, type_table[1]);
    g_hash_table_insert(braille_table, ending_double_bar, type_table[2]);
    g_hash_table_insert(braille_table, sectional_double_bar, type_table[2]);

    for(i=0; i<3; i++) 
	g_hash_table_insert(braille_table, clefs[i], type_table[3]);

    g_hash_table_insert(braille_table, dot, type_table[4]);

    for(i=0; i<5; i++) 
	g_hash_table_insert(braille_table, fingerings[i], type_table[5]);

    for(i=0; i<3; i++) 
	g_hash_table_insert(braille_table, in_accords[i], type_table[6]);
    
    for(i=0; i<7; i++) 
	g_hash_table_insert(braille_table, intervals[i], type_table[7]);

    for(i=0; i<28; i++) 
	g_hash_table_insert(braille_table, notes[i], type_table[8]);

    for(i=0; i<7; i++) 
	g_hash_table_insert(braille_table, octaves[i], type_table[9]);
    
    for(i=0; i<9; i++) 
	g_hash_table_insert(braille_table, ornaments[i], type_table[10]);
    
    for(i=0; i<10; i++) 
	  g_hash_table_insert(braille_table, repetitons_tremolo[i], type_table[11]);
      
    for(i=0; i<4; i++) 
	g_hash_table_insert(braille_table, rests[i], type_table[12]);
    
    for(i=0; i<13; i++) 
	g_hash_table_insert(braille_table, slurs_ties[i], type_table[13]);
    for(i=0; i<6; i++) 
	g_hash_table_insert(braille_table, stems[i], type_table[14]);

    for(i=0; i<6; i++) 
	g_hash_table_insert(braille_table, tuplet[i], type_table[15]);
	
    g_hash_table_insert(braille_table, right_hand, type_table[16]);
    g_hash_table_insert(braille_table, left_hand, type_table[16]);

}

void init_colors() {
    static int initialised = 0;
    if(!initialised) {
	int i;
	for(i = 0; i < NB_TYPES; i++) 
	    gdk_color_parse(default_color_table[i], &color_table[i]);
	
	initialised = 1;
    }
}

void set_tags(GtkTextBuffer *buffer) {
    GtkTextIter start, end;
    GtkTextTagTable *tag_table = gtk_text_buffer_get_tag_table(buffer);

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    GtkTextTag *tag;
    int i;
    for(i = 0; i< NB_TYPES; i++) {
	tag = gtk_text_tag_table_lookup(tag_table, type_table[i]);
	if(tag) 
	    gtk_text_tag_table_remove(tag_table, tag);
	
	gtk_text_buffer_create_tag(buffer, type_table[i], "foreground", 
				   gdk_color_to_string(&color_table[i]), NULL); 
    }
}

/**
 * \fn void color(BrailleMusicEditor *editor)
 * \brief This function color the differents types of braille music notations
 * in the textview.
 * \param editor The structure holding the data.
 * 
 * This function will color the diffrents types of braille music notations present in text. 
 */

void color(BrailleMusicEditor *editor)
{
    GtkTextIter start, end;
    GtkTextIter start_match, end_match, start_match2, start_match3;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    gtk_text_buffer_get_start_iter(buffer, &start_match);
    gtk_text_buffer_get_start_iter(buffer, &end_match);
    
    set_tags(buffer);
    init_braille_table();
    
    do {
	gtk_text_iter_forward_chars(&end_match, 1);
	gchar *c = gtk_text_iter_get_slice(&start_match, &end_match);
	
	start_match2 = start_match;
	gtk_text_iter_backward_chars(&start_match2, 1);
	gchar *c2 = gtk_text_iter_get_slice(&start_match2, &end_match);
	
	start_match3 = start_match2;
	gtk_text_iter_backward_chars(&start_match3, 1);
	gchar *c3 = gtk_text_iter_get_slice(&start_match3, &end_match);

	gchar *type;
	if((type = g_hash_table_lookup(braille_table, c3)) != NULL) {
	    gtk_text_buffer_remove_all_tags(buffer, &start_match3, &end_match);
	    gtk_text_buffer_apply_tag_by_name(buffer, type, &start_match3, &end_match);
	}
	else if((type = g_hash_table_lookup(braille_table, c2)) != NULL) {
	    gtk_text_buffer_remove_all_tags(buffer, &start_match2, &end_match);
	    gtk_text_buffer_apply_tag_by_name(buffer, type, &start_match2, &end_match);
	}
	else if((type = g_hash_table_lookup(braille_table, c)) != NULL) {
	    gtk_text_buffer_apply_tag_by_name(buffer, type, &start_match, &end_match);
	}
	
    } while(gtk_text_iter_forward_chars(&start_match, 1));
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
    
    init_colors();
    
    GtkWidget *buttons[NB_TYPES];
    int i;
    for(i = 0; i < NB_TYPES; i++) {
	buttons[i] = gtk_button_new_with_label(type_table[i]);

	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), buttons[i], 
			   TRUE, TRUE, 0);
    
	g_signal_connect(G_OBJECT(buttons[i]),"clicked", 
			 G_CALLBACK(color_selection), editor);
    
	gtk_widget_modify_bg(buttons[i], GTK_STATE_NORMAL, &color_table[i]);
    }
    gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
    
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); 
    GtkStyle *style;

    // run the dialog window
    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	    for(i = 0; i < NB_TYPES; i++) {
		//retrieving the colors selected by the user
		style = gtk_widget_get_style(buttons[i]);
		color_table[i] = style->bg[GTK_STATE_NORMAL];
	    }
	    //updating the coloration
	    set_tags(buffer);
	    coloration_update(widget, editor);
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
