import ch.supsi.webapp.models.BlogPost;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.apache.commons.lang.RandomStringUtils;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

@Ignore("this class only shows how to use ObjectMapper. I don't want to test others' code")
public class JacksonTest {
    ObjectMapper mapper;
    Path path;
    File file;

    @Before
    public void CreateFile() throws IOException {
        mapper = new ObjectMapper();
        path = Paths.get("./data.json");

        Files.createDirectories(path.getParent());

        try {
            Files.createFile(path);
        } catch (FileAlreadyExistsException e) {
            //already exists
        } finally {
            file = new File(path.toUri());
        }
    }


    @Test
    public void MapperWriteToFileTest() throws IOException {
        BlogPost bp = new BlogPost("uno","due","tre");
        mapper.writeValue(file,bp);
    }

    @Test
    public void MapperReadFromFileTest() throws IOException {
        BlogPost bp = mapper.readValue(file, BlogPost.class);
    }

    @Test
    public void MapperWriteMoreThanOneToFileTest() throws IOException {



        List<BlogPost> listBlogPosts = new ArrayList<>();

        for (int i =0; i<5; i++) {
            listBlogPosts.add(new BlogPost(
                    RandomStringUtils.randomAlphabetic(5),
                    RandomStringUtils.randomAlphabetic(5),
                    RandomStringUtils.randomAlphabetic(5)));
        }

        //     JsonGenerator generator = mapper.getFactory().createGenerator(file, JsonEncoding.UTF8); lo uso se voglio fare append su file
        //     mapper.writeValue(generator,valueToWrite);

        mapper.writeValue(file,listBlogPosts);


    }



    @Test
    public void MapperReadMoreThanOneFromFileTest() throws IOException {

        mapper.configure(DeserializationFeature.USE_JAVA_ARRAY_FOR_JSON_ARRAY, true);
        List<BlogPost> blogPosts = mapper.readValue(file, new TypeReference<List<BlogPost>>(){});

    }


}
