///////////////////////////////////////////////////////////
// Usage IEprompt("dialog descriptive text", "default starting value");
// 
// IEprompt will call promptCallback(val)
// Where val is the user's input or null if the dialog was canceled.
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// This source code has been released into the public domain
// January 14th, 2007.
// You may use it and modify it freely without compensation
// and without the need to tell everyone where you got it.
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// You must create a promptCallback(val) function to handle
// the user input.  If you don't this script will fail and
// Bunnies will die.
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// These are global scope variables, they should remain global.
///////////////////////////////////////////////////////////
var _dialogPromptID=null;
var _blackoutPromptID=null;
///////////////////////////////////////////////////////////

function IEprompt(innertxt,def) {

   that=this;

   // Check to see if this is MSIE 7.   This isn't a great general purpose
   // detection system but it works well enough just to find MSIE 7.
   var _isIE7=(navigator.userAgent.indexOf('MSIE 7')>0);

   this.wrapupPrompt = function (cancled) {
      // wrapupPrompt is called when the user enters or cancels the box.
      // It's called only by the IE7 dialog box, not the non IE prompt box
      if (_isIE7) {
         // Make sure we're in IE7 mode and get the text box value
         val=document.getElementById('iepromptfield').value;
         // clear out the dialog box
         _dialogPromptID.style.display='none';
         // clear out the screen
         _blackoutPromptID.style.display='none';
         // clear out the text field
         document.getElementById('iepromptfield').value = '';
         // if the cancel button was pushed, force value to null.
         if (cancled) { val = ''; }
         // call the user's function
         promptCallback(val);
      }
      return false;
   }

   //if def wasn't actually passed, initialize it to null
   if (def==undefined) { def=''; }

   if (_isIE7) {
      // If this is MSIE 7.0 then...
      if (_dialogPromptID==null) {
         // Check to see if we've created the dialog divisions.
         // This block sets up the divisons
         // Get the body tag in the dom
         var tbody = document.getElementsByTagName("body")[0];
         // create a new division
         tnode = document.createElement('div');
         // name it
         tnode.id='IEPromptBox';
         // attach the new division to the body tag
         tbody.appendChild(tnode);
         // and save the element reference in a global variable
         _dialogPromptID=document.getElementById('IEPromptBox');
         // Create a new division (blackout)
         tnode = document.createElement('div');
         // name it.
         tnode.id='promptBlackout';
         // attach it to body.
         tbody.appendChild(tnode);
         // And get the element reference
         _blackoutPromptID=document.getElementById('promptBlackout');
         // assign the styles to the blackout division.
         _blackoutPromptID.style.opacity='.9';
         _blackoutPromptID.style.position='absolute';
         _blackoutPromptID.style.top='0px';
         _blackoutPromptID.style.left='0px';
         _blackoutPromptID.style.backgroundColor='#555555';
         _blackoutPromptID.style.filter='alpha(opacity=90)';
         _blackoutPromptID.style.height=(document.body.offsetHeight<screen.height) ? screen.height+'px' : document.body.offsetHeight+20+'px'; 
         _blackoutPromptID.style.display='block';
         _blackoutPromptID.style.zIndex='50';
         // assign the styles to the dialog box
         _dialogPromptID.style.border='2px solid blue';
         _dialogPromptID.style.backgroundColor='#DDDDDD';
         _dialogPromptID.style.position='absolute';
         _dialogPromptID.style.width='330px';
         _dialogPromptID.style.zIndex='100';
      }
      // This is the HTML which makes up the dialog box, it will be inserted into
      // innerHTML later. We insert into a temporary variable because
      // it's very, very slow doing multiple innerHTML injections, it's much
      // more efficient to use a variable and then do one LARGE injection.
      var tmp = '<div style="width: 100%; background-color: blue; color: white; font-family: verdana; font-size: 10pt; font-weight: bold; height: 20px">Input Required</div>';
      tmp += '<div style="padding: 10px">'+innertxt + '<BR><BR>';
      tmp += '<form action="" onsubmit="return that.wrapupPrompt()">';
      tmp += '<input id="iepromptfield" name="iepromptdata" type=text size=46 value="'+def+'">';
      tmp += '<br><br><center>';
      tmp += '<input type="submit" value="&nbsp;&nbsp;&nbsp;OK&nbsp;&nbsp;&nbsp;">';
      tmp += '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
      tmp += '<input type="button" onclick="that.wrapupPrompt(true)" value="&nbsp;Cancel&nbsp;">';
      tmp += '</form></div>';
      // Stretch the blackout division to fill the entire document
      // and make it visible.  Because it has a high z-index it should
      // make all other elements on the page unclickable.
      _blackoutPromptID.style.height=(document.body.offsetHeight<screen.height) ? screen.height+'px' : document.body.offsetHeight+20+'px'; 
      _blackoutPromptID.style.width='100%';
      _blackoutPromptID.style.display='block';
      // Insert the tmp HTML string into the dialog box.
      // Then position the dialog box on the screen and make it visible.
      _dialogPromptID.innerHTML=tmp;
      _dialogPromptID.style.top=parseInt(document.documentElement.scrollTop+(screen.height/3))+'px';
      _dialogPromptID.style.left=parseInt((document.body.offsetWidth-315)/2)+'px';
      _dialogPromptID.style.display='block';
      // Give the dialog box's input field the focus.
      document.getElementById('iepromptfield').focus();
   } else {
      // we are not using IE7 so do things "normally"
      promptCallback(prompt(innertxt,def));
   }
}
