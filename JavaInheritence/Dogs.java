package Dogs;

public class Dogs {
    private String name;
    private char gender;
    private String type;
    private String color;
    private String size;

    public Dogs() {
        System.out.println("Parent constructor with no arguments");
    }

    public Dogs(String n, char g, String t, String c, String s) {
        name = n;
        gender = g;
        type = t;
        color = c;
        size = s;
    }

    public char get_gender() { return gender; }
    public String get_type() { return type; }
    public String get_color() { return color; }
    public String get_size() { return size; }

    public void get_info() {
        System.out.println("Name: " + name);
        System.out.println("Dog type: " + type);
        System.out.println("Color: " + color);
        System.out.println("Gender: " + gender);
        System.out.println("Size: " + size);
    }

    public void message() {
        System.out.println("Parent message");
    }
}
