# JSP & Servlet Demo (with optional H2 database)

This is a minimal JSP + Servlet application demonstrating client-server communication and an optional database-backed feature using H2.

## Structure
- `src/main/webapp/index.jsp`: Form that posts to `HelloServlet`.
- `src/main/java/com/example/web/HelloServlet.java`: Reads form data and renders a response.
- `src/main/webapp/WEB-INF/web.xml`: Servlet mappings and welcome file.
- `src/main/java/com/example/web/DbUtil.java`: H2 DB helper and schema bootstrap.
- `src/main/java/com/example/web/MessageServlet.java`: Saves and lists messages using H2.
- `src/main/webapp/messages.jsp`: UI to add/list messages from DB.

## Prerequisites
- Java 8+
- Maven 3.8+

## Run (Jetty)
```bash
mvn clean package
mvn jetty:run
```
Then open `http://localhost:8080/` in your browser.

## Notes
- Data is stored in an H2 file DB under `./data/messages_db`.
- You can disable DB features by ignoring the `/messages` page; the HelloServlet works independently.



