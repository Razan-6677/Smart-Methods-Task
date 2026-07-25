# Task 3 - Voice Assistant

## Problem

The voice chatbot was not working. Any message sent resulted in a generic error, "An error occurred while connecting to the server," with no further details.

## Solution Steps

1. Opened DevTools and monitored the Network tab, and found that the request to `chat.php` was returning a 404 error (file not found at the expected path).
2. Discovered that InfinityFree hosting automatically blocks any file with "chat" in its name (a security measure against live chat scripts that overload the server). Renamed the file to `process.php` and updated the path in `app.js`.
3. After renaming, a 500 error appeared (internal server error), so I recreated the file from scratch instead of relying on the rename, which resolved the issue.
4. Verified that the Gemini API key was valid and active from Google AI Studio, and updated the model name since `gemini-2.0-flash` had been deprecated.
5. Modified the code to return the actual error details (instead of a generic message), which made it much easier to pinpoint each issue quickly.
6. Noticed that the bot's replies were displayed without proper spacing or paragraphs, and that Markdown symbols such as `##` and `**` appeared as raw text instead of being formatted. The cause was that the code used `textContent`, which prints any symbol as plain text. Added a function to convert the formatting into headings and bold text and to break lines properly, along with a security sanitization function beforehand, and a second function to clean the text so the text-to-speech feature reads it naturally without saying words like "hashtag" or "asterisk."
7. Updated the colors in `style.css` (background, bubbles, buttons) for a different visual style.

## Live Site

The website is deployed using [InfinityFree](https://infinityfree.com) hosting.

🔗 [taskai.kesug.com](https://taskai.kesug.com/)

## Website Preview

![Website Preview](./screenshots/preview.png)

## Files

- [index.html](./index.html) — Page structure and chat interface
- [style.css](./style.css) — Styling, layout, and UI color theme
- [app.js](./app.js) — Speech recognition, text-to-speech, and communication with the backend
- [process.php](./process.php) — Backend script that securely calls the Gemini API
- [config.php](./config.php) — API key configuration
- [.htaccess](./.htaccess) — Protects config.php from direct browser access

## Tech Used
