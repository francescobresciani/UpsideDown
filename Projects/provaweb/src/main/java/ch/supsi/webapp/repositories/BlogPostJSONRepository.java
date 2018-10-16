package ch.supsi.webapp.repositories;

import ch.supsi.webapp.models.BlogPost;
import com.fasterxml.jackson.core.JsonEncoding;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.File;
import java.io.IOException;

public class BlogPostJSONRepository {

    private static BlogPostJSONRepository instance = new BlogPostJSONRepository();
    private String path = "./data.json";
    private final File file;
    private final ObjectMapper mapper;
    private JsonGenerator generator;

    public static BlogPostJSONRepository getInstance() {
        return instance;
    }

    private BlogPostJSONRepository() {
        file = new File(path);
        mapper = new ObjectMapper();
        try{

            generator = mapper.getFactory().createGenerator(file, JsonEncoding.UTF8);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public BlogPost save(final BlogPost bp) {

        try {

            mapper.writeValue(generator,bp);
            return bp;
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            System.out.println("BlogPostJSONRepository.save() ->"+bp);
        }
        return null;
    }
}
