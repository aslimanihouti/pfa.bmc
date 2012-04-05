#include <gtk/gtk.h>
#include <evince-view.h>

void show_score(GtkWidget *w) {
    GError *err = NULL;
    GFile *file;
    gchar *filename = "score.pdf";
    file = g_file_new_for_commandline_arg (filename);
    gchar *uri = g_file_get_uri (file);
    g_object_unref (file);
    EvDocument *doc = ev_document_factory_get_document (uri, &err);
    if(err) {
	g_warning ("Trying to read the score pdf file %s gave an error: %s", uri, err->message);
	if(err)
	    g_error_free (err);
	err = NULL;
    } else {
	EvDocumentModel *docmodel = ev_document_model_new_with_document(EV_DOCUMENT(doc)); 
	GtkWidget *scoreview = ev_view_new();
	ev_view_set_model(EV_VIEW(scoreview), EV_DOCUMENT_MODEL(docmodel));
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(w), scoreview);	
    }
}
