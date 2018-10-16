package ch.supsi.webapp.controllers;

import ch.supsi.webapp.models.BlogPost;
import ch.supsi.webapp.services.BlogPostService;

public class BlogPostController implements MyController {


    private static final BlogPostController instance = new BlogPostController();
    private final BlogPostService service;

    //private constructor to avoid client applications to use constructor
    private BlogPostController(){
        this.service = BlogPostService.getInstance();
    }

    public static BlogPostController getInstance(){
        return instance;
    }

    public BlogPost save(BlogPost bp) {
        return service.save(bp);
    }
}
