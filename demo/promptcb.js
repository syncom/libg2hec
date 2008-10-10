// IEprompt Callback function to handle choose random prime request
function promptCallback(val) {

  if ( val != null ) {
  var size = val.trim();

  if ( size == "" ) alert("Must enter nonnegative integral value");

  else if ( isNumeric(size) ) {
      if (size > 1400) alert("Size too large. Please choose one <= 1400");
      else {
        document.demoform.primesize.value=size;
        document.demoform.buttontype.value="Random";
        document.demoform.submit();
      }
    }
  else {
    alert("Must enter nonnegative integral value");
    }
  }
}

<!-- Check non-negative nemeric -->
function isNumeric(sText)
{
   var ValidChars = "0123456789";
   var IsNumber=true;
   var Char;

   for (var i = 0 ; i < sText.length && IsNumber == true; i++) 
      { 
      Char = sText.charAt(i); 
      if (ValidChars.indexOf(Char) == -1) 
         {
         IsNumber = false;
         }
      }
   return IsNumber;
   
   }

String.prototype.trim=function(){
    return this.replace(/^\s*|\s*$/g,'');
}

String.prototype.ltrim=function(){
    return this.replace(/^\s*/g,'');
}

String.prototype.rtrim=function(){
    return this.replace(/\s*$/g,'');
}
