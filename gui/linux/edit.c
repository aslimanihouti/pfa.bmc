#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"


void on_copy(GtkWidget *widget, BrailleMusicEditor *editor)
{
	g_signal_emit_by_name(editor->textview, "copy-clipboard", NULL);
}

void on_cut(GtkWidget *widget, BrailleMusicEditor *editor)
{
	g_signal_emit_by_name(editor->textview, "cut-clipboard", NULL);
}

void on_paste(GtkWidget *widget, BrailleMusicEditor *editor)
{
	g_signal_emit_by_name(editor->textview, "paste-clipboard", NULL);
}
