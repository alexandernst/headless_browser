Headless browser based on WebKit
================

This tool will help you make your AJAX applications crawlable.

Webpages based on JavaSript MVC libraries can't be positioned
by default because search engines can't run (yet) all the
JavaSript code that your page needs to execute in order to *show*
anything. That's why you need a headless browser that will fetch
the page, run the JavaSript and output the resulting HTML to the
crawler, which will then be able to index your page.

The entire project is under 50 lines of code so you won't have 
any trouble understanding it. It's based on Qt4 so it should work
on all operating systems. There's also a small example written in
PHP, but you're free to use it however you want.

There's one small *thing* that you should know about this headless
browser. It will output everything as UTF-8. Most of the time this
works like a charm, but there are also a lot of pages that don't
use any encoding, or set one encoding in the headers, but the
content has another. Most browsers try to guess what encoding are
using the pages you make it open, and that's ok with most pages,
but there are some exceptions. And that's why I don't want to play
the same game of trying to guess the encoding. Instead I'm leaving
that part to you, dear developer :)