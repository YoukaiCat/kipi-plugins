/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2017-03-09
 * Description : a tool to use reverse image search engines api
 *
 * Copyright (C) 2017 Vladislav Mileshkin
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

function replaceCurrentDocument(doc) {
    // Not using XMLSerializer because of it's sanitizer broke js
    var html = doc.documentElement.outerHTML;
    document.open();
    document.write(html);
    document.close();
}

function addBaseURL(doc, url) {
    var head = doc.head;
    var base = doc.createElement("base");
    base.setAttribute("href", url);
    head.insertBefore(base, head.firstChild);
}

function showMessage(message) {
    document.getElementById("progress").innerHTML = message;
    console.log(message);
}

function base64ToByteArray(base64) {
    showMessage("Please wait... Decoding image");
    var binaryString = atob(base64);
    var binaryStringLength = binaryString.length;
    var buffer = new ArrayBuffer(binaryString.length);
    var byteArray = new Uint8Array(buffer);
    var i;
    for (i = 0; i < binaryStringLength; i++) {
        byteArray[i] = binaryString.charCodeAt(i);
    }
    showMessage("Please wait...");
    return byteArray;
}

function sendRequest(url, baseUrl, formData) {
    var request = new XMLHttpRequest();

    request.responseType = "document";

    request.onreadystatechange = function () {
        switch (request.readyState) {
        case XMLHttpRequest.UNSENT:
            showMessage("Please wait... Request created");
            break;
        case XMLHttpRequest.OPENED:
            showMessage("Please wait... Request opened");
            break;
        case XMLHttpRequest.HEADERS_RECEIVED:
            showMessage("Please wait... Sending data");
            break;
        case XMLHttpRequest.LOADING:
            showMessage("Please wait... Receiving answer");
            break;
        case XMLHttpRequest.DONE:
            showMessage("Please wait... Data transfer completed");
            if (request.status === 200) {
                var newDocument = request.response;
                addBaseURL(newDocument, baseUrl);
                replaceCurrentDocument(newDocument);
            } else {
                showMessage(`Error: HTTP status code ${request.status}`);
            }
            break;
        }
    };

    request.onerror = function () {
        showMessage("An error occurred during the request!");
    };

    request.withCredentials = true;
    request.open("POST", url, true);
    request.send(formData);
}
