#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <iostream>
#include <gtkmm/cssprovider.h>
#include <gdkmm/screen.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h> 

class HelloWorld : public Gtk::Window
{
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    void on_button_clicked(const std::string &button_name);
    Gtk::Button m_button1, m_button2, m_button3; // Declare three buttons
    Gtk::Box m_box;                              // A container to hold the label, entry, and buttons
    Gtk::Box m_button_box;                       // A container to hold the buttons horizontally
    Gtk::Label m_label;                          // Declare a label
    Gtk::Entry m_entry;                          // Declare an entry widget
};

HelloWorld::HelloWorld()
    : m_button1("Button 1"), m_button2("Button 2"), m_button3("Button 3"),
      m_label("Enter text below:"), m_entry() // Initialize label and entry
{
    // Set window properties
    set_title("NOTION");

    // Initialize the box container (vertical layout for label and entry)
    m_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_box.set_homogeneous(false); // Allow varying button sizes
    m_box.set_spacing(20);        // Add space between elements in the container

    // Customize button margins
    m_button1.set_margin_top(10);    // External padding around button 1
    m_button1.set_margin_bottom(10); // External padding around button 1
    m_button1.set_margin_right(10);
    m_button1.set_margin_left(10);

    m_button2.set_margin_top(10);    // External padding around button 2
    m_button2.set_margin_bottom(10); // External padding around button 2
    m_button2.set_margin_right(10);
    m_button2.set_margin_left(10);

    m_button3.set_margin_top(10);    // External padding around button 3
    m_button3.set_margin_bottom(10); // External padding around button 3
    m_button3.set_margin_right(10);
    m_button3.set_margin_left(10);
    // Set buttons to expand in the box (optional but ensures resizing)
    m_button1.set_hexpand(true);
    m_button2.set_hexpand(true);
    m_button3.set_hexpand(true);

    // Load and apply CSS styles with padding and glowing effect
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(R"(
        button {
            background-color: lightblue;
            color: darkblue;
            font: bold 14px Arial;
            border-radius: 10px;
            padding: 15px 20px; /* 15px padding top-bottom, 20px left-right */
            transition: box-shadow 0.3s ease;
        }

        button:hover {
            box-shadow: 0 0 15px 5px rgba(0, 0, 255, 0.7);  /* Glowing blue on hover */
        }

        button:active {
            box-shadow: 0 0 25px 10px rgba(0, 0, 255, 1);   /* Stronger glow on click */
        }
    )");

    // Apply the CSS to the buttons' style context
    auto screen = Gdk::Screen::get_default();
    m_button1.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_button2.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_button3.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create a new box for the buttons (horizontal layout)
    m_button_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL); // Set horizontal orientation
    m_button_box.set_homogeneous(true);                        // Make buttons the same size
    m_button_box.set_spacing(10);                              // Add space between buttons

    // Add buttons to the horizontal button box
    m_button_box.pack_start(m_button1);
    m_button_box.pack_start(m_button2);
    m_button_box.pack_start(m_button3);

    // Add the label, entry, and button box to the main container
    m_box.pack_start(m_label);      // Add label above entry
    m_box.pack_start(m_entry);      // Add entry below the label
    m_box.pack_start(m_button_box); // Add the button box (horizontal layout)

    // Connect signals
    m_button1.signal_clicked().connect([this]()
                                       { on_button_clicked("Button 1"); });
    m_button2.signal_clicked().connect([this]()
                                       { on_button_clicked("Button 2"); });
    m_button3.signal_clicked().connect([this]()
                                       { on_button_clicked("Button 3"); });

    // Add the box container to the window
    add(m_box);

    // Display all children
    show_all_children();
}

HelloWorld::~HelloWorld() {}

void HelloWorld::on_button_clicked(const std::string &button_name)
{
    // Retrieve the text entered in the entry field
    std::string entered_text = m_entry.get_text();
    std::cout << button_name << " clicked! Entered text: " << entered_text << std::endl;
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "com.example.GtkExample");
    HelloWorld helloworld;
    return app->run(helloworld);
}
