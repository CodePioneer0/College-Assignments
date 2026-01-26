package com.example.web;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

// Annotation is optional since web.xml maps /hello, but keeping it helps IDEs
@WebServlet(name = "HelloServlet", urlPatterns = {"/hello"})
public class HelloServlet extends HttpServlet {

  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    response.setContentType("text/html;charset=UTF-8");
    try (PrintWriter out = response.getWriter()) {
      out.println("<!DOCTYPE html>");
      out.println("<html><head><meta charset='UTF-8'><title>Hello Servlet</title></head><body>");
      out.println("<h2>Use the form on the home page to POST a message.</h2>");
      out.println("<a href='index.jsp'>Back to Home</a>");
      out.println("</body></html>");
    }
  }

  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String name = request.getParameter("name");
    String message = request.getParameter("message");

    if (name == null) name = "Anonymous";
    if (message == null) message = "";

    response.setContentType("text/html;charset=UTF-8");
    try (PrintWriter out = response.getWriter()) {
      out.println("<!DOCTYPE html>");
      out.println("<html><head><meta charset='UTF-8'><title>Hello Response</title></head><body>");
      out.println("<h1>Server Response</h1>");
      out.printf("<p><strong>Name:</strong> %s</p>", escapeHtml(name));
      out.printf("<p><strong>Message:</strong> %s</p>", escapeHtml(message));
      out.println("<a href='index.jsp'>Back</a>");
      out.println("</body></html>");
    }
  }

  private String escapeHtml(String s) {
    return s
      .replace("&", "&amp;")
      .replace("<", "&lt;")
      .replace(">", "&gt;")
      .replace("\"", "&quot;")
      .replace("'", "&#x27;");
  }
}




