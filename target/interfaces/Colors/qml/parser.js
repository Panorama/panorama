function readField(sourceData, field) {
    var regexp = new RegExp("\\s+" + field + "\\s*=\\s*([^$]+?)\\s*;", "");
    var match = sourceData.match(regexp);

    if(match != null && match.length > 1) {
        var data = match[1];
        if(data.charAt(0) == '"') {
            data = data.substring(1, data.length - 1);
            return data;
        }
        else if(/^-?\d+$/.test(data)) {
            return parseInt(data);
        }
        else if(/^0x[a-fA-F0-9]{8}$/.test(data)) {
            data = data.substring(2).toLowerCase();
            var a = data.substring(6, 8);
            data = data.substring(0, 6);
            data = "#" + a + data;
            return data;
        }
        else {
            print("Warning: Could not parse \"" + data + "\"");
            return "";
        }
    }
    print("Warning: field \"" + field + "\" not found");
    return null;
}
