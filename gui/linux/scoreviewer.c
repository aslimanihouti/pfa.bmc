/**
 * \file scoreviewer.c
 * \brief Scoreviewer creating functions.
 * \author Team BMC
 * \version 1.0
 * \date 07 April 2012
 *
 * Scoreviewer creating functions.
 *
 */

#include <gtk/gtk.h>
#include <evince-view.h>
#include <stdlib.h>

/**
 * \fn void external_link_catch(GtkWidget *w, GObject *link) 
 * \brief This function catch the signal when a clic is made on a note.
 * \param w The widget which triggered the call.
 * \param link ev_link_action.
 * 
 */
void external_link_catch(GtkWidget *w, GObject *link) {
    EvLinkAction *l = EV_LINK_ACTION(link);
    ev_view_copy_link_address(EV_VIEW(w), l);
    
    printf("%s\n", ev_link_action_get_uri(l));
}

/**
 * \fn void show_score(GtkWidget *w) 
 * \brief This function create a scoreviewer in a widget.
 * \param w The widget in which th scoreviewer will be created.
 */
void show_score(GtkWidget *w) {
    GError *err = NULL;
    GFile *file;
    gchar *filename = "score.pdf";
    file = g_file_new_for_commandline_arg (filename);
    gchar *uri = g_file_get_uri (file);
    g_object_unref (file);
    EvDocument *doc = ev_document_factory_get_document (uri, &err);
    if(err) {
	g_warning ("Trying to read the score pdf file %s gave an error: %s",
		   uri, err->message);
	if(err)
	    g_error_free (err);
	err = NULL;
    } else {
	EvDocumentModel *docmodel = ev_document_model_new_with_document(EV_DOCUMENT(doc)); 
	GtkWidget *scoreview = ev_view_new();
	ev_view_set_model(EV_VIEW(scoreview), EV_DOCUMENT_MODEL(docmodel));
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(w), scoreview);	
	g_signal_connect(scoreview, "external-link", 
			 G_CALLBACK(external_link_catch), NULL);
    }
}
