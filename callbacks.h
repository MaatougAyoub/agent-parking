#include <gtk/gtk.h>


void on_ajouter_clicked(GtkButton *objet_graphique, gpointer user_data);



void on_continuer_clicked(GtkButton *objet_graphique, gpointer user_data);

void on_modifier_clicked(GtkButton *objet_graphique, gpointer user_data);

int on_ccontinuer_clicked(GtkButton *objet_graphique, gpointer user_data);



void on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void on_supprimerlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data);

void on_modifierlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data);

void on_ajouterlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data);

void on_listereservation_clicked(GtkButton *objet_graphique, gpointer user_data);

void on_okreservation_clicked(GtkButton *objet_graphique, gpointer user_data);
