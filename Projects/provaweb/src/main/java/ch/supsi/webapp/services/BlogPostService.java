package ch.supsi.webapp.services;

import ch.supsi.webapp.models.BlogPost;
import ch.supsi.webapp.repositories.BlogPostJSONRepository;

public class BlogPostService implements MyService {

    private static final BlogPostService instance = new BlogPostService();
    private final BlogPostJSONRepository repository = BlogPostJSONRepository.getInstance();

    //private constructor to avoid client applications to use constructor
    private BlogPostService(){

    }

    public static BlogPostService getInstance(){
        return instance;
    }

    public BlogPost save(final BlogPost bp){
        return repository.save(bp);

    }
}
