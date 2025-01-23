#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <iostream>
#include <gtkmm/cssprovider.h>
#include <gdkmm/screen.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/listbox.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gio/gio.h>
#include <vector>
#include <glibmm/ustring.h>

#include <string>
#include <fstream>
#include <cstdlib> // For std::system
#include <string>  // For std::string

class HelloWorld : public Gtk::Window
{
public:
    HelloWorld();
    virtual ~HelloWorld();
    int n = 0;
    char text[100];

protected:
    void on_button_clicked(const std::string &button_name);
    void on_AddTask_clicked(const std::string &add_button)
    {
        std::string entry_text = m_entry.get_text();
        if (!entry_text.empty())
        {
            int task_no = n + 1;                                                 // Clearer variable name for 'no'
            auto label = Gtk::make_managed<Gtk::Label>(std::to_string(task_no)); // Create a label with the task number
            std::string text = m_entry.get_text();                               // Retrieve text from the entry

            tasks.pack_start(*label); // Add the label to the container
            m_entry.set_text("");
        }
    }
    Gtk::Button m_button1, m_button2, m_button3; // Declare three buttons
    Gtk::Box m_box;                              // A container to hold the label, entry, and buttons
    Gtk::Box m_button_box;                       // A container to hold the buttons vertically
    Gtk::Box m_entry_box;                        // A container to hold the buttons vertically

    Gtk::Box welcome_box;
    Gtk::Label m_label; // Declare a label
    Gtk::Button add_task;
    Gtk::Entry m_entry; // Declare an entry widget
    bool label_replaced = false;
    Gtk::Grid grid;
    Gtk::Box add_task_space;
    bool on_entry_clicked(GdkEventButton *event);
    Gtk::Box tasks;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
};

HelloWorld::HelloWorld()
    : m_button1(""), m_button2(""), m_button3(""),
      m_label("Welcom !!, Let's Start New Coding Session") // m_entry() // Initialize label and entry
{
    // Set window properties
    set_title("NOTION");
    set_default_size(700, 500);

    // Initialize the box container (horizontal layout for label and entry)
    m_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    m_box.set_homogeneous(false); // Allow varying button sizes
    m_box.set_spacing(10);        // Add space between elements in the container

    // Load images
    auto image1 = Gtk::make_managed<Gtk::Image>("icons/icon1.png");
    auto image2 = Gtk::make_managed<Gtk::Image>("icons/icon2.png");
    auto image3 = Gtk::make_managed<Gtk::Image>("icons/icon3.png");

    // Resize images to 32x32
    auto pixbuf1 = Gdk::Pixbuf::create_from_file("icons/icon1.png");
    auto pixbuf2 = Gdk::Pixbuf::create_from_file("icons/icon2.png");
    auto pixbuf3 = Gdk::Pixbuf::create_from_file("icons/icon3.png");

    image1->set(pixbuf1->scale_simple(32, 32, Gdk::INTERP_BILINEAR));
    image2->set(pixbuf2->scale_simple(32, 32, Gdk::INTERP_BILINEAR));
    image3->set(pixbuf3->scale_simple(32, 32, Gdk::INTERP_BILINEAR));

    // Attach images to buttons
    m_button1.set_image(*image1);
    m_button2.set_image(*image2);
    m_button3.set_image(*image3);

    // Ensure images are always shown
    m_button1.set_always_show_image(true);
    m_button2.set_always_show_image(true);
    m_button3.set_always_show_image(true);

    // Set fixed size and disable expansion for buttons

    m_button1.set_size_request(80, 50);
    m_button2.set_size_request(80, 50);
    m_button3.set_size_request(80, 50);

    // Initialize the grid layout for buttons
    grid.set_row_spacing(15);    // Set spacing between rows
    grid.set_column_spacing(15); // Set spacing between columns

    grid.attach(m_button1, 0, 0);
    grid.attach(m_button2, 0, 1);
    grid.attach(m_button3, 0, 2);

    // Load and apply CSS styles from a file
    auto css_provider = Gtk::CssProvider::create();

    // // Correctly load the CSS file
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path("style.css");
    css_provider->load_from_file(file);

    // Apply the CSS to the buttons' style context
    auto screen = Gdk::Screen::get_default();
    m_button1.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_button2.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_button3.get_style_context()->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    m_button1.signal_enter_notify_event().connect([&](GdkEventCrossing *)
                                                  { m_button1.override_background_color(Gdk::RGBA("blue")); return false; });

    m_button1.signal_leave_notify_event().connect([&](GdkEventCrossing *)
                                                  {  m_button1.unset_background_color();  return false; });

    // Create a new box for the buttons (horizontal layout)
    m_button_box.set_orientation(Gtk::ORIENTATION_VERTICAL); // Set horizontal orientation
    m_button_box.set_homogeneous(true);                      // Make buttons the same size
    m_button_box.set_spacing(10);                            // Add space between buttons

    // Disable expansion for each button
    m_button1.set_hexpand(false);
    m_button1.set_vexpand(false);
    m_button2.set_hexpand(false);
    m_button2.set_vexpand(false);
    m_button3.set_hexpand(false);
    m_button3.set_vexpand(false);

    // Add buttons to the horizontal button box
    // Add buttons to the button box without expansion
    m_button_box.pack_start(m_button1, Gtk::PACK_SHRINK);
    m_button_box.pack_start(m_button2, Gtk::PACK_SHRINK);
    m_button_box.pack_start(m_button3, Gtk::PACK_SHRINK);

    grid.set_row_spacing(15);    // Set spacing between rows
    grid.set_column_spacing(15); // Set spacing between columns
    grid.set_margin_left(10);

    grid.attach(m_button1, 0, 0);
    grid.attach(m_button2, 0, 1);
    grid.attach(m_button3, 0, 2);

    grid.set_valign(Gtk::ALIGN_CENTER); // Center the grid vertically

    // Add components to the main box
    m_box.pack_start(grid, Gtk::PACK_SHRINK);
    m_box.pack_start(m_label);

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
    // std::string entered_text = m_entry.get_text(); // Get the current text from the entry widget

    if (button_name == "Button 1")
    {
        // github
        // m_entry.set_text(""); // Clear the entry box

        const char *url = "https://github.com/amgadalharazi";

        // Platform-specific command
#ifdef _WIN32
        std::string command = "start " + std::string(url); // Windows
#elif __linux__
        std::string command = "xdg-open " + std::string(url); // Linux
#elif __APPLE__
        std::string command = "open " + std::string(url); // macOS
#else
#error "Unsupported platform"
#endif

        std::system(command.c_str()); // Execute the command
    }

    else if (button_name == "Button 2")
    {
        // m_entry.set_text("Hello, Gtkmm!"); // Set predefined text in the entry
        std::cout << button_name << " clicked! Set predefined text." << std::endl;
    }
    if (button_name == "Button 3" && !label_replaced)
    {
        // Remove the label and add the entry
        m_box.remove(m_label);

        m_entry.set_placeholder_text("Enter your task here...");
        m_entry_box.set_margin_top(20);
        m_entry_box.set_margin_left(10);
        add_task.set_label("Add");
        add_task.signal_clicked().connect([this]()
                                          { on_AddTask_clicked("add"); });
        add_task.set_margin_left(10);
        add_task.set_size_request(80, 50);
        add_task.set_margin_right(10);

        add_task_space.pack_start(m_entry);
        add_task_space.pack_start(add_task, Gtk::PACK_SHRINK);
        add_task_space.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

        m_entry_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        m_entry_box.pack_start(add_task_space, Gtk::PACK_SHRINK);

        tasks.set_orientation(Gtk::ORIENTATION_VERTICAL);
        tasks.pack_start(m_entry_box, Gtk::PACK_SHRINK);

        m_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        m_box.pack_start(tasks);

        // label_replaced = true;
        show_all_children();
    }
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "hizbu.com"); // Widgets
    HelloWorld helloworld;
    return app->run(helloworld);
}
