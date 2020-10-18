#include <gtk/gtk.h>
#include <stdio.h>
#include "../Controller/GameController/GameController.h"
#include "../Controller/PlayerController/PlayerController.h"
GtkWidget * image;
GtkWidget * image2;
GtkWidget * button_box; 
GtkBuilder * builder; 
GtkWidget * window;
GtkWidget * second_window;
GtkWidget * third_window;
GtkEntry * text_entry;
GtkWidget * lbl_one;
GtkWidget * lbl_two;
GtkWidget * lbl_three;
GtkWidget * lbl_four;
GtkWidget * lbl_five;
GtkWidget * button;
GtkWidget * list_chooser_one;
GtkWidget * list_chooser_two;
GtkWidget * list_chooser_three;

static void my_callback(GObject *source_object, GAsyncResult *res, gpointer user_data){}

void on_name_entry_chaged(GtkEntry * text_entry, gpointer data){
    char * entry;
    g_print(" %s\n", gtk_entry_get_text(GTK_ENTRY(text_entry)));
    // setName((char *)gtk_entry_get_text(GTK_ENTRY(text_entry)));
}


static void start_async(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable)
{
    startGame();
}

void on_ready_button_clicked(GtkWidget * ready_button, gpointer data){
    /* Ventana donde se lleva a cabo la batalla
    Deben de mostrarse las estructuras de datos correspondientes */

    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
    gtk_widget_hide(second_window);

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "Interface.glade", NULL);
    third_window = GTK_WIDGET (gtk_builder_get_object (builder, "Battle_window")); 
    if (NULL == third_window)
    {
        fprintf(stderr, "Unable to file object with id \"Battle_window\" \n");
    }
    lbl_one = GTK_WIDGET(gtk_builder_get_object(builder, "attack_info"));
    lbl_two = GTK_WIDGET(gtk_builder_get_object(builder, "pokemon1"));
    lbl_three = GTK_WIDGET(gtk_builder_get_object(builder, "pokemon2"));
    lbl_four = GTK_WIDGET(gtk_builder_get_object(builder, "energy1"));
    lbl_five = GTK_WIDGET(gtk_builder_get_object(builder, "energy2"));
    image = GTK_WIDGET(gtk_builder_get_object(builder, "sprite1"));
    image2 = GTK_WIDGET(gtk_builder_get_object(builder, "sprite2"));
    /* A las imagenes debe de asignarle el correspondiente sprite */
    /* Igualmente con el Pokemon name, HP y energy que debe de ir disminuyendo en cada ocación
    En attacks info debe de actualizarse el contenido cada vez que se realice una batalla */

    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(third_window);

}

void on_start_button_clicked(GtkWidget * start_button, gpointer data){
    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
    gtk_widget_hide(window);

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "Interface.glade", NULL);
    second_window = GTK_WIDGET (gtk_builder_get_object (builder, "second_window")); 
    if (NULL == second_window)
    {
        fprintf(stderr, "Unable to file object with id \"second_window\" \n");
    }

    lbl_one = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    text_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name_entry"));
    list_chooser_one = GTK_WIDGET(gtk_builder_get_object(builder, "first_pokemon_list"));
    list_chooser_two = GTK_WIDGET(gtk_builder_get_object(builder, "second_pokemon_list"));
    list_chooser_three = GTK_WIDGET(gtk_builder_get_object(builder, "third_pokemon_list"));
    button_box = GTK_WIDGET(gtk_builder_get_object(builder, "ready_button_box"));
    button =  GTK_WIDGET(gtk_builder_get_object(builder, "ready_button"));
    /* Agregar los textos a los widgets de seleccionar pokemon */
    g_signal_connect (button, "clicked", G_CALLBACK (on_ready_button_clicked), NULL);
    g_signal_connect (text_entry, "activate", G_CALLBACK (on_name_entry_chaged), text_entry);
    gtk_entry_set_text (GTK_ENTRY (text_entry), "");
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(second_window);

}

void on_window_destroyed(){
    gtk_main_quit();
}

static void activate(GtkApplication *app, gpointer user_data){

    initialize_data();

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
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
    text_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name_entry"));
    g_signal_connect (button, "clicked", G_CALLBACK (on_start_button_clicked), NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char * argv[]){
    GtkApplication *app;
    int status;

    app = gtk_application_new("pthreadmon.simulator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
