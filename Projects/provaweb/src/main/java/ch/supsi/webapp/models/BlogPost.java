package ch.supsi.webapp.models;

import org.apache.commons.lang.RandomStringUtils;

public class BlogPost {
    private String title;
    private String text;
    private String author;


    public BlogPost() { }

    public BlogPost(String title, String text, String author) {
        this.title = title;
        this.text = text;
        this.author = author;
    }

    public BlogPost(final BlogPost bp) {
        this.title = bp.title;
        this.text = bp.text;
        this.author = bp.author;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    @Override
    public String toString() {
        return "title: "+title+" text: "+text+" author: "+author;
    }

    public static BlogPost getWithRandomValues(){
        return new BlogPost(
                RandomStringUtils.randomAlphabetic(3),
                RandomStringUtils.randomAlphabetic(4),
                RandomStringUtils.randomAlphabetic(5));
    }
}
