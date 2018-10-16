package ch.supsi.webapp;

import ch.supsi.webapp.controllers.BlogPostController;
import ch.supsi.webapp.models.BlogPost;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.File;
import java.io.IOException;

import javax.rmi.CORBA.ValueHandler;
import javax.servlet.ServletException;
import javax.servlet.ServletInputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(value="/blogposts")
@SuppressWarnings("serial")
public class BlogPostsServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.getWriter().println("ciao");
    }

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {

        String title;
        String text;
        String author;
        BlogPost bp;
        ObjectMapper mapper = new ObjectMapper();
	    switch(req.getContentType()){
            case "application/json":
                bp=mapper.readValue(req.getReader(), BlogPost.class);
                break;

            case "application/x-www-form-urlencoded":
                title = req.getParameter("title");
                text = req.getParameter("text");
                author = req.getParameter("author");
                bp = new BlogPost(title,text,author);
                break;
            default:
                throw new ServletException("Post request not handled");
                //TODO quale è il comportamento giusto?
        }
        BlogPostController.getInstance().save(bp);
        mapper.writeValue(res.getWriter(),bp);

	}
    
}
