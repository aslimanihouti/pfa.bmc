#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"

/**
 * \file edit.c
 * \author Team BMC editor 
 */
/**
 * edit menu callback 
 */


/**
 * \fn void on_undo(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_undo(GtkWidget *widget, BrailleMusicEditor *editor)
{
    g_signal_emit_by_name(editor->textview, "undo", NULL);
}

/**
 * \fn void on_redo(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_redo(GtkWidget *widget, BrailleMusicEditor *editor)
{
    g_signal_emit_by_name(editor->textview, "redo", NULL);
}


/**
 * \fn void on_copy(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_copy(GtkWidget *widget, BrailleMusicEditor *editor)
{
    g_signal_emit_by_name(editor->textview, "copy-clipboard", NULL);
}

/**
 * \fn void on_cut(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_cut(GtkWidget *widget, BrailleMusicEditor *editor)
{
    g_signal_emit_by_name(editor->textview, "cut-clipboard", NULL);
}

/**
 * \fn void on_paste(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_paste(GtkWidget *widget, BrailleMusicEditor *editor)
{
    g_signal_emit_by_name(editor->textview, "paste-clipboard", NULL);
}

/**
 * \fn void on_select_all(GtkWidget *widget, BrailleMusicEditor *editor)
 */
void on_select_all(GtkWidget *widget, BrailleMusicEditor *editor)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview));
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_get_end_iter(buffer,&end);
    gtk_text_buffer_create_mark(buffer, "selection_bound", &start, FALSE);
    gtk_text_buffer_move_mark_by_name(buffer, "insert", &end);
}

/* void on_select(GtkWidget *widget, BrailleMusicEditor *editor) */
/* { */
/* 	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview)); */

/* 	GtkTextMark *mark_cursor = gtk_text_buffer_get_mark (buffer, "insert"); */
/* 	GtkTextIter iter_cursor; */

/* 	gtk_text_buffer_get_iter_at_mark(buffer, &iter_cursor, mark_cursor); */
	
/* 	gtk_text_buffer_create_mark(buffer, "selection_bound", &iter_cursor, FALSE); */
	
/* } */


