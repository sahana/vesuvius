function testNumber(src) {
     var emailReg = "[0-9]+";
     var regex = new RegExp(emailReg);
     return regex.test(src);
}
