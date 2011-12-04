#include <gtk/gtk.h>

extern GtkWidget *text_view;

void on_copy()
{
	g_signal_emit_by_name(text_view, "copy-clipboard", NULL);
}

void on_cut()
{
	g_signal_emit_by_name(text_view, "cut-clipboard", NULL);
}

void on_paste()
{
	g_signal_emit_by_name(text_view, "paste-clipboard", NULL);
}
