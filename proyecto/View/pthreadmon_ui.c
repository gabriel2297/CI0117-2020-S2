#include <gtk/gtk.h>

static void print_message (GtkWidget *widget, gpointer data) {
    g_print ("Pokemon Go Battle Simulator\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;
    GtkWidget * image;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Pthreadmon");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);

    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    image = gtk_image_new_from_file ("/Images/Pokemon_logo.png");
    gtk_container_add(GTK_CONTAINER (window), image);

    button = gtk_button_new_with_label ("Start!");
    g_signal_connect (button, "clicked", G_CALLBACK (print_message), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all (window);
}

int
main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("pthreadmon.simulator.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}