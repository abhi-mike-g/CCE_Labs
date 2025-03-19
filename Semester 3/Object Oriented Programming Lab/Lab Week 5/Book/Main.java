import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class Book 
{
    private String title;
    private String author;
    private int edition;

    public Book(String title, String author, int edition) 
    {
        this.title = title;
        this.author = author;
        this.edition = edition;
    }

    public String getTitle() 
    {
        return title;
    }

    public String getAuthor() 
    {
        return author;
    }

    public int getEdition() 
    {
        return edition;
    }

    public void display() 
    {
        System.out.println("Title: " + title + ", Author: " + author + ", Edition: " + edition);
    }
}

public class Main {
    public static void main(String[] args) 
    {
        // Creating a list of books
        List<Book> books = new ArrayList<>();

        // Adding Book objects to the list
        books.add(new Book("Java Programming", "John Doe", 3));
        books.add(new Book("Effective Java", "Joshua Bloch", 2));
        books.add(new Book("Clean Code", "Robert C. Martin", 1));
        books.add(new Book("Design Patterns", "Erich Gamma", 1));
        books.add(new Book("Head First Java", "Kathy Sierra", 2));
        books.add(new Book("The Pragmatic Programmer", "Andrew Hunt", 1));
        books.add(new Book("Java: The Complete Reference", "Herbert Schildt", 9));
        books.add(new Book("C: The Complete Reference", "Herbert Schildt", 8));
        books.add(new Book("Python: The Complete Reference", "Martin Brown", 5));
        books.add(new Book("C++: The Complete Reference", "Herbert Schildt", 10));
        books.add(new Book("Digital Design", "Morris Mano", 12));
        books.add(new Book("Data and Computer Communication", "William Stallings", 8));
        books.add(new Book("The Java Handbook", "Herbert Schildt", 9));
        books.add(new Book("Cryptography and Network Security", "William Stallings", 9));
        books.add(new Book("Let us C", "Yashwant Katnekar", 7));
        books.add(new Book("Let us C++", "Yashwant Katnekar", 7));
        books.add(new Book("Let us Java", "Yashwant Katnekar", 5));
        books.add(new Book("Let us SQL", "Yashwant Katnekar", 3));
        books.add(new Book("Let us R", "Yashwant Katnekar", 6));
        books.add(new Book("Digital Communications and Networking", "B. Fouruzan", 6));
        books.add(new Book("Six Easy Pieces", "Richard P. Feynman", 1));
        books.add(new Book("Six Not so Easy Pieces", "Richard P. Feynman", 1));
        books.add(new Book("Hilarious isn't it, Mr.Feynman", "Richard P. Feynman", 1));
        books.add(new Book("The Feynman Lectures on Physics Volume 1", "Richard P. Feynman", 1));
        books.add(new Book("The Feynman Lectures on Physics Volume 2", "Richard P. Feynman", 1));
        books.add(new Book("The Feynman Lectures on Physics Volume 3", "Richard P. Feynman", 1));
        books.add(new Book("Concepts of Physics", "H C Verma", 1));
        books.add(new Book("Head First SQL", "Kathy Sierra", 2));

        // Sorting the list of books in ascending order by title
        Collections.sort(books, new Comparator<Book>() 
        {
            @Override
            public int compare(Book b1, Book b2) 
            {
                return b1.getTitle().compareTo(b2.getTitle());
            }
        });

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the author's name to search for their books: ");
        String authorName = scanner.nextLine();
        scanner.close();

        boolean found = false;
        for (Book book : books) 
        {
            if (book.getAuthor().equalsIgnoreCase(authorName)) 
            {
                book.display();
                found = true;
            }
        }

        if (!found) 
        {
            System.out.println("No books found by the author " + authorName + ".");
        }
    }
}