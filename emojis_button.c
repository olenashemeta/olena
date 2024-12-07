#include "../inc/client.h"

GtkWidget *emoji_window = NULL;
GtkWidget *message_entry;

void on_emoji_selected(GtkButton *button, gpointer user_data) {
    (void) user_data;  
    const char *emoji = gtk_button_get_label(button);  
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(message_entry));

    gchar *new_text = g_strdup_printf("%s%s", current_text, emoji);
    gtk_entry_set_text(GTK_ENTRY(message_entry), new_text);
    g_free(new_text);
}

void on_emoji_button_clicked(GtkButton *button, gpointer user_data) {
    (void)button;   
    (void)user_data; 

    if (emoji_window) {
        gtk_widget_destroy(emoji_window);
        emoji_window = NULL;
    } else {
        emoji_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(emoji_window), "Виберіть емодзі");
        gtk_window_set_default_size(GTK_WINDOW(emoji_window), 200, 200);

        GtkWidget *emoji_grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(emoji_window), emoji_grid);

        const char *emojis[] = {
            "😊", "😂", "😢", "😍", "😎", "😡", "🥰", "😘", "😋", "🤗",
            "😃", "😄", "😅", "😜", "😏", "😇", "😱", "🥺", "😆", "👽",
            "🥳", "👻", "🤡", "👍", "👎", "💖", "💔", "❤️", "✨", "💫",
            "🌚", "🌻", "🌱", "🐱", "🐶", "🐝", "🦋", "🧚‍♀️", "👀", "🥴"
        };

        int num_emojis = sizeof(emojis) / sizeof(emojis[0]);

        for (int i = 0; i < num_emojis; i++) {
            GtkWidget *emoji_button = gtk_button_new_with_label(emojis[i]);
            g_signal_connect(emoji_button, "clicked", G_CALLBACK(on_emoji_selected), NULL);
            gtk_grid_attach(GTK_GRID(emoji_grid), emoji_button, i % 5, i / 5, 1, 1);
        }

        gtk_widget_show_all(emoji_window);
    }
}
