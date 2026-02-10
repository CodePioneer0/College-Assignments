<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Messages (DB)</title>
    <style>
      body { font-family: Arial, sans-serif; margin: 2rem; }
      table { border-collapse: collapse; width: 100%; margin-top: 1rem; }
      th, td { border: 1px solid #ccc; padding: 0.5rem; text-align: left; }
      form { margin-top: 1rem; }
      input[type=text], textarea { width: 360px; padding: 0.5rem; }
    </style>
  </head>
  <body>
    <h1>Saved Messages (H2 Database)</h1>
    <div>
      <a href="index.jsp">Back to Home</a>
    </div>

    <h2>Add a new message</h2>
    <c:if test="${not empty error}">
      <div style="color: red;">${error}</div>
    </c:if>
    <form action="messages" method="post">
      <label for="name">Your Name</label>
      <input id="name" name="name" type="text" placeholder="Alice" />

      <label for="message">Message</label>
      <textarea id="message" name="message" rows="3" placeholder="This will be stored in H2" required></textarea>

      <div style="margin-top: 0.5rem;">
        <button type="submit">Save Message</button>
      </div>
    </form>

    <h2>All messages</h2>
    <c:choose>
      <c:when test="${empty rows}">
        <p>No messages yet.</p>
      </c:when>
      <c:otherwise>
        <table>
          <thead>
            <tr>
              <th>ID</th>
              <th>Name</th>
              <th>Message</th>
              <th>Created At</th>
            </tr>
          </thead>
          <tbody>
            <c:forEach var="r" items="${rows}">
              <tr>
                <td>${r.id}</td>
                <td>${r.name}</td>
                <td>
                  <c:out value="${r.message}"/>
                </td>
                <td>${r.created_at}</td>
              </tr>
            </c:forEach>
          </tbody>
        </table>
      </c:otherwise>
    </c:choose>
  </body>
  </html>



