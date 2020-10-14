#include <gtk/gtk.h>
#include <stdio.h>
//#include "Controller/GameController/GameController.h"
GtkWidget * image;
GtkWidget * button_box;

void on_name_entry_chaged(GtkEntry * text_entry, gpointer data){
    char * entry;
    g_print("Player's name: %s\n", gtk_entry_get_text(GTK_ENTRY(text_entry)));
    g_print("Player's name set!\n");
}

void on_start_button_clicked(GtkWidget * start_button, gpointer data){
    
    GtkBuilder * builder; 
    GtkWidget * window;
    GtkEntry * text_entry;
    GtkWidget * lbl_one;
    
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "Interface.glade", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "second_window")); 
    if (NULL == window)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"second_window\" \n");
        /* Your error handling code goes here */
    }
    lbl_one = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    text_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name_entry"));
    g_signal_connect (text_entry, "activate", G_CALLBACK (on_name_entry_chaged), text_entry);
    gtk_entry_set_text (GTK_ENTRY (text_entry), "Player's name");
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
}

void on_window_destroyed(){
    gtk_main_quit();
}



int main(int argc, char * argv[]){
    GtkBuilder * builder; 
    GtkWidget * window;
    GtkWidget * button;
	//initialize_data();

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "Interface.glade", NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1")); 
    if (NULL == window)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"window1\" \n");
        /* Your error handling code goes here */
    }
    image = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    button_box = GTK_WIDGET(gtk_builder_get_object(builder, "button_box"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));

    g_signal_connect (button, "clicked", G_CALLBACK (on_start_button_clicked), NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

