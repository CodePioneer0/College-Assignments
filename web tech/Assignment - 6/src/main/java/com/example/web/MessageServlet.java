package com.example.web;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedHashMap;
import java.util.Map;

@WebServlet(name = "MessageServlet", urlPatterns = {"/messages"})
public class MessageServlet extends HttpServlet {

  @Override
  public void init() throws ServletException {
    try {
      DbUtil.ensureSchema();
    } catch (SQLException e) {
      throw new ServletException("Failed to ensure DB schema", e);
    }
  }

  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    try {
      List<Map<String, Object>> rows = fetchMessages();
      request.setAttribute("rows", rows);
      request.getRequestDispatcher("/messages.jsp").forward(request, response);
    } catch (SQLException e) {
      throw new ServletException("Failed to fetch messages", e);
    }
  }

  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String name = request.getParameter("name");
    String message = request.getParameter("message");
    if (name == null || name.trim().isEmpty()) {
      name = "Anonymous";
    }
    if (message == null || message.trim().isEmpty()) {
      request.setAttribute("error", "Message is required");
      doGet(request, response);
      return;
    }
    try {
      saveMessage(name.trim(), message.trim());
      response.sendRedirect(request.getContextPath() + "/messages");
    } catch (SQLException e) {
      throw new ServletException("Failed to save message", e);
    }
  }

  private void saveMessage(String name, String message) throws SQLException {
    String sql = "INSERT INTO messages (name, message) VALUES (?, ?)";
    try (Connection conn = DbUtil.getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
      ps.setString(1, name);
      ps.setString(2, message);
      ps.executeUpdate();
    }
  }

  private List<Map<String, Object>> fetchMessages() throws SQLException {
    String sql = "SELECT id, name, message, created_at FROM messages ORDER BY created_at DESC";
    List<Map<String, Object>> out = new ArrayList<>();
    try (Connection conn = DbUtil.getConnection(); PreparedStatement ps = conn.prepareStatement(sql); ResultSet rs = ps.executeQuery()) {
      while (rs.next()) {
        Map<String, Object> row = new LinkedHashMap<>();
        row.put("id", rs.getLong("id"));
        row.put("name", rs.getString("name"));
        row.put("message", rs.getString("message"));
        row.put("created_at", rs.getTimestamp("created_at"));
        out.add(row);
      }
    }
    return out;
  }
}




