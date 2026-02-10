const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = process.env.PORT || 3000;

const escapeHtml = value =>
    String(value)
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#39;');

const server = http.createServer((req, res) => {
    const baseUrl = req.headers.host ? `http://${req.headers.host}` : `http://localhost:${PORT}`;
    const requestUrl = new URL(req.url, baseUrl);

    if (requestUrl.pathname === '/submit' && req.method === 'GET') {
        const name = requestUrl.searchParams.get('name') || '';
        const email = requestUrl.searchParams.get('email') || '';
        const message = requestUrl.searchParams.get('message') || '';

        console.log('Data received from client:');
        console.log('Name   :', name ? escapeHtml(name) : 'Not provided');
        console.log('Email  :', email ? escapeHtml(email) : 'Not provided');
        console.log('Message:', message ? escapeHtml(message) : 'Not provided');

        res.writeHead(204);
        res.end();
    } else if ((requestUrl.pathname === '/' || requestUrl.pathname === '/client') && req.method === 'GET') {
        const clientPath = path.join(__dirname, 'client.html');
        fs.readFile(clientPath, (err, data) => {
            if (err) {
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end('Failed to load client page');
                return;
            }

            res.writeHead(200, { 'Content-Type': 'text/html; charset=UTF-8' });
            res.end(data);
        });
    } else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('Not Found');
    }
});

server.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});

