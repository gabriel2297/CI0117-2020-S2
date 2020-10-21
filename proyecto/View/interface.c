#include <gtk/gtk.h>
#include <stdio.h>
#include "../Controller/GameController/GameController.h"
#include "../Controller/PlayerController/PlayerController.h"
#include "../Model/mapper.h"
#include <stdlib.h>
#include <string.h>
int id_matrix[2][3];
char pokemonName1[200]; 
char pokemonName2[200];
char path[200] = "sprites/";
char path2[200] = "sprites/";
char pokemon1_hp[200];
char pokemon2_hp[200];
char pokemon1_energy[200];
char pokemon2_energy[200];
char pokemon1_moveNameAndDamage[200];
char pokemon2_moveNameAndDamage[200];
char estadisticas[500];
GtkWidget * image;
GtkWidget * sprite1;
GtkWidget * sprite2;
GtkWidget * button_box; 
GtkBuilder * builder; 
GtkWidget * window;
GtkWidget * second_window;
GtkWidget * third_window;
GtkWidget * lbl_one;
GtkWidget * lbl_two;
GtkWidget * lbl_three;
GtkWidget * lbl_four;
GtkWidget * lbl_five;
GtkWidget * button;
GtkComboBoxText * list_chooser_one;
GtkComboBoxText * list_chooser_two;
GtkComboBoxText * list_chooser_three;
GtkComboBoxText * list_chooser_four;
GtkComboBoxText * list_chooser_five;
GtkComboBoxText * list_chooser_six;

static void my_callback(GObject *source_object, GAsyncResult *res, gpointer user_data){}

static void start_async(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable)
{
    startGame(id_matrix);
}

void setPokemonName(int playerId, char * name){
    if (playerId == 1){
        strcpy(pokemonName1, name);
        //gtk_image_clear(GTK_IMAGE(sprite1));
        memset(path, 0, sizeof path);
        strcpy(path,"sprites/");
        strcat(path, getPokemonName());
        strcat(path, ".png");
        printf("PATH: %s", path);
        gtk_image_set_from_file(GTK_IMAGE(sprite1), path);
        gtk_image_set_from_pixbuf(GTK_IMAGE(sprite1), gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(sprite1)), 100, 100, GDK_INTERP_NEAREST));
    }
    else {
        strcpy(pokemonName2, name);
        //gtk_image_clear(GTK_IMAGE(sprite2));
        memset(path2, 0, sizeof path2);
        strcpy(path2,"sprites/");
        strcat(path2, getPokemon2Name());
        strcat(path2, ".png");
        printf("PATH: %s", path2);
        gtk_image_set_from_file(GTK_IMAGE(sprite2), path2);
        gtk_image_set_from_pixbuf(GTK_IMAGE(sprite2), gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(sprite2)), 100, 100, GDK_INTERP_NEAREST));
        
    }
}

char * getPokemonName(){
    return pokemonName1;
}

char * getPokemon2Name(){
    return pokemonName2;
}

void setPokemonHP(int playerId, int hp)
{
    printf("Setting hp %d for player %d\n", hp, playerId);
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_hp, "%s, yo te elijo!\nVida: %d", getPokemonName(), hp);
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
    }
    else
    {
        int n = sprintf(pokemon2_hp, "%s, yo te elijo!\nVida: %d", getPokemon2Name(), hp);
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
    }
}

void setWinnerInformation(int playerId, char * name) {
    if (playerId == 1)
    {
        printf("Jugador 1 es el ganador\n");
        int n = sprintf(pokemon1_hp, "Felicidades %s, el jugador %d es el ganador!\n", name, playerId);
        sprintf(pokemon2_hp, "-");
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
        n = sprintf(pokemon1_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
        n = sprintf(pokemon2_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
    }
    else {
        printf("Jugador 2 es el ganador\n");
        int n = sprintf(pokemon2_hp, "Felicidades %s, el jugador %d es el ganador!\n", name, playerId);
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
        sprintf(pokemon1_hp, "-");
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
        n = sprintf(pokemon2_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
        n = sprintf(pokemon1_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
    }
}

void setPokemonEnergy(int playerId, int energy) 
{
    printf("Setting energy %d for player %d\n", energy, playerId);
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_energy, "Energia aculumada: %d", energy);
        gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
    }
    else
    {
        int n = sprintf(pokemon2_energy, "Energia acumulada: %d", energy);
        gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
    }
}

void setFastAttackName(int playerId, char * moveName, int damage)
{
    printf("Setting attack %s with damage %d for player %d\n", moveName, damage, playerId);
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque rapido!\nAtaque: %s\nDaño: %d\n", getPokemonName(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon1_moveNameAndDamage);
    }
    else
    {
        int n = sprintf(pokemon2_moveNameAndDamage, "%s, usa ataque rapido!\nAtaque: %s\nDaño: %d\n", getPokemon2Name(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon2_moveNameAndDamage);
    }
}

void setChargedAttackName(int playerId, char * moveName, int damage)
{
    printf("Setting attack %s with damage %d for player %d\n", moveName, damage, playerId);
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque cargado!\nAtaque: %s\nDaño: %d\n", getPokemonName(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon1_moveNameAndDamage);
    }
    else
    {
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque cargado!\nAtaque: %s\nDaño: %d\n", getPokemon2Name(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon2_moveNameAndDamage);
    }
}

void setPokemonStatistics(unsigned long pokemon_statistics[3][3], pokemon_t* player1_pokemons[MAX_POKEMONS_PER_PLAYER], pokemon_t* player2_pokemons[MAX_POKEMONS_PER_PLAYER])
{
    printf("mostrando estadisticas\n");
    int n = sprintf(estadisticas, "Estadisticas del juego:\n \
        Duracion total: %lu segundos\n \
        Pokemons jugador 1:\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        Pokemons jugador 2:\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n",
        pokemon_statistics[2][0],
        player1_pokemons[0]->pokemon_info->speciesName, pokemon_statistics[0][0],
        player1_pokemons[1]->pokemon_info->speciesName, pokemon_statistics[0][1],
        player1_pokemons[2]->pokemon_info->speciesName, pokemon_statistics[0][2],
        player2_pokemons[0]->pokemon_info->speciesName, pokemon_statistics[1][0],
        player2_pokemons[1]->pokemon_info->speciesName, pokemon_statistics[1][1],
        player2_pokemons[2]->pokemon_info->speciesName, pokemon_statistics[1][2]
    );
    printf("%s\n", estadisticas);
    gtk_label_set_text(GTK_LABEL(lbl_one), estadisticas);
}

void on_box1_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][0] = (int)gtk_combo_box_get_active(comboBox);
}

void on_box2_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][1] = (int)gtk_combo_box_get_active(comboBox);
}

void on_box3_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][2] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box4_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][0] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box5_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][1] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box6_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][2] = (int)gtk_combo_box_get_active(comboBox);
}

void on_ready_button_clicked(GtkWidget * ready_button, gpointer data){
    
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
    sprite1 = GTK_WIDGET(gtk_builder_get_object(builder, "sprite1"));
    sprite2 = GTK_WIDGET(gtk_builder_get_object(builder, "sprite2"));

    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(third_window);

}

void on_start_button_clicked(GtkWidget * start_button, gpointer data){

    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
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
    list_chooser_one = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box1"));
    list_chooser_two = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box2"));
    list_chooser_three = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box3"));
    list_chooser_four = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box4"));
    list_chooser_five = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box5"));
    list_chooser_six = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box6"));

    for (size_t i = 0; i < NUM_POKEMON; ++i){
        gtk_combo_box_text_append(list_chooser_one, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_two, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_three, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_four, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_five, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_six, NULL, (gchar *) get_pokemon_species_name(i));
    }
    button_box = GTK_WIDGET(gtk_builder_get_object(builder, "button_box"));
    button =  GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    
    /* Agregar los textos a los widgets de seleccionar pokemon */
    g_signal_connect (button, "clicked", G_CALLBACK (on_ready_button_clicked), NULL);
    g_signal_connect (list_chooser_one, "changed", G_CALLBACK (on_box1_changed), NULL);
    g_signal_connect (list_chooser_two, "changed", G_CALLBACK (on_box2_changed), NULL);
    g_signal_connect (list_chooser_three, "changed", G_CALLBACK (on_box3_changed), NULL);
    g_signal_connect (list_chooser_four, "changed", G_CALLBACK (on_box4_changed), NULL);
    g_signal_connect (list_chooser_five, "changed", G_CALLBACK (on_box5_changed), NULL);
    g_signal_connect (list_chooser_six, "changed", G_CALLBACK (on_box6_changed), NULL);

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