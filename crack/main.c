#include <gtk/gtk.h>
#include <vlc/vlc.h>

// Window settings.
const int   WINDOW_WIDTH               = 750;
const int   WINDOW_HEIGHT              = 500;
const char* WINDOW_NAME                = "CrackMe Problem";
const char* BACKGROUND_GIF_NAME        = "background.gif";
const char*    SUCCESS_GIF_NAME        = "success.gif";
const char*  PATCH_SUCCESS_WINDOW_NAME = "Patch Successful";
const char* KEYGEN_SUCCESS_WINDOW_NAME = "Key copied to clipboard";

// Crack button settings.
const int   CRACK_BUTTON_WIDTH        = 230;
const int   CRACK_BUTTON_COORDINATE_X = 455;
const int   CRACK_BUTTON_COORDINATE_Y = 222;
const char* CRACK_BUTTON_LABEL        = "Crack";

// Keygen button settings.
const int   KEYGEN_BUTTON_WIDTH        = 330;
const int   KEYGEN_BUTTON_COORDINATE_X = 405;
const int   KEYGEN_BUTTON_COORDINATE_Y = 340;
const char* KEYGEN_BUTTON_LABEL        = "Crack";

// Keygen output settings.
const int   KEYGEN_OUTPUT_WIDTH        = 330;
const int   KEYGEN_OUTPUT_COORDINATE_X = 405;
const int   KEYGEN_OUTPUT_COORDINATE_Y = 400;

// File chooser settings.
#define     FILE_CHOOSER_MSG            "Choose file you'd like to crack"
const int   FILE_CHOOSER_WIDTH        = 330;
const int   FILE_CHOOSER_COORDINATE_X = 405;
const int   FILE_CHOOSER_COORDINATE_Y = 105;

// Music settings
const char* MUSIC_FILE_NAME = "music.mp3";

// File chooser settings.
const char* CHOOSER_LABEL_MSG          = FILE_CHOOSER_MSG;
const int   CHOOSER_LABEL_COORDINATE_X = WINDOW_WIDTH / 2; 
const int   CHOOSER_LABEL_COORDINATE_Y = FILE_CHOOSER_COORDINATE_Y - 100;

GtkWidget* setup_window        ();
GtkWidget* setup_fixed         (GtkWidget* window);
void       setup_file_chooser  (GtkWidget* fixed);
void       setup_background_gif(GtkWidget* fixed);
void       setup_crack_button  (GtkWidget* fixed, GCallback callback);
void       setup_keygen_button (GtkWidget* fixed, GCallback callback);
void       show_success_popup  (const char* window_name);

libvlc_media_player_t* music_contructor(const char* file_name);

void on_crack_button_clicked(GtkWidget* button, gpointer user_data)
{
    show_success_popup(PATCH_SUCCESS_WINDOW_NAME);
}

void on_keygen_button_clicked(GtkWidget* button, gpointer user_data)
{
    show_success_popup(KEYGEN_SUCCESS_WINDOW_NAME);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    music_contructor(MUSIC_FILE_NAME);

    GtkWidget* window = setup_window();

    GtkWidget* fixed = setup_fixed(window);

    setup_background_gif    (fixed);
    setup_file_chooser      (fixed);
    setup_crack_button      (fixed, G_CALLBACK( on_crack_button_clicked));
    setup_keygen_button     (fixed, G_CALLBACK(on_keygen_button_clicked));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


libvlc_media_player_t* music_contructor(const char* file_name)
{

    libvlc_instance_t* inst   = libvlc_new(0, NULL);
    libvlc_media_t*    m      = libvlc_media_new_path(inst, file_name);
    libvlc_media_player_t *mp = libvlc_media_player_new_from_media(m);

    // release the media now.
    libvlc_media_release(m);

    // play the media_player
    libvlc_media_player_play(mp);
}

GtkWidget* setup_window()
{
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title       (GTK_WINDOW(window), WINDOW_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH,
                                                    WINDOW_HEIGHT);

    return window;
}

void show_success_popup(const char* window_name)
{
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title    (GTK_WINDOW(window), window_name);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget* background = gtk_image_new_from_file(SUCCESS_GIF_NAME);
    gtk_container_add(GTK_CONTAINER(window), background);

    gtk_widget_show_all(window);
}

GtkWidget* setup_fixed(GtkWidget* window)
{
    GtkWidget* fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    return fixed;
}

void setup_background_gif(GtkWidget* fixed)
{
    GtkWidget* background = gtk_image_new_from_file(BACKGROUND_GIF_NAME);
    gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);
}

void setup_file_chooser(GtkWidget* fixed)
{
    GtkWidget* file_chooser = gtk_file_chooser_button_new(FILE_CHOOSER_MSG,
                                                  GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_widget_set_size_request(file_chooser, FILE_CHOOSER_WIDTH, -1);
    gtk_widget_set_opacity(file_chooser, 0.0);

    gtk_fixed_put(GTK_FIXED(fixed), file_chooser, FILE_CHOOSER_COORDINATE_X,
                                                  FILE_CHOOSER_COORDINATE_Y);
}

void setup_crack_button(GtkWidget* fixed, GCallback callback)
{
    GtkWidget* button = gtk_button_new_with_label(CRACK_BUTTON_LABEL);
    gtk_widget_set_size_request(button, CRACK_BUTTON_WIDTH, -1);

    gtk_widget_set_opacity(button, 0.0);

    g_signal_connect(button, "clicked", callback, NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button, CRACK_BUTTON_COORDINATE_X,
                                            CRACK_BUTTON_COORDINATE_Y);
}

void setup_keygen_button(GtkWidget* fixed, GCallback callback)
{
    GtkWidget* button = gtk_button_new_with_label(KEYGEN_BUTTON_LABEL);
    gtk_widget_set_size_request(button, KEYGEN_BUTTON_WIDTH, -1);

    gtk_widget_set_opacity(button, 0.0);

    g_signal_connect(button, "clicked", callback, NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button, KEYGEN_BUTTON_COORDINATE_X,
                                            KEYGEN_BUTTON_COORDINATE_Y);
}








