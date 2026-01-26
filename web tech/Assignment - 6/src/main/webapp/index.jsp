<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>JSP & Servlet Demo</title>
    <style>
      body { font-family: Arial, sans-serif; margin: 2rem; }
      form { margin-bottom: 2rem; }
      label { display: block; margin: 0.5rem 0 0.25rem; }
      input[type=text], textarea { width: 320px; padding: 0.5rem; }
      button { padding: 0.5rem 1rem; }
      .links a { margin-right: 1rem; }
    </style>
  </head>
  <body>
    <h1>Client-Server Communication (JSP ↔ Servlet)</h1>

    <h2>Send a greeting to the server</h2>
    <form action="hello" method="post">
      <label for="name">Your Name</label>
      <input id="name" name="name" type="text" placeholder="Alice" required />

      <label for="message">Message</label>
      <textarea id="message" name="message" rows="3" placeholder="Hello from JSP!" required></textarea>

      <div style="margin-top: 0.75rem;">
        <button type="submit">Send to HelloServlet</button>
      </div>
    </form>

    <div class="links">
      <a href="messages">View saved messages (DB optional)</a>
    </div>
  </body>
  </html>



