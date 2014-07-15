CK Editor Browser
======

## Overview
This module allows you to specify a view to be used as the source for a wysiwyg popup. This view should contain a list of links; when a link is selected, and the dialog's ok button is clicked, the link will be inserted into the wysiwyg.

## Installation
- Do the standard module install steps.

## Configuration
- Create a view to be used with the CK Browser.
- This view should contain a list of links (CK Browser will inject the href and text from the selected link).
- For the best experience, enable ajax for your view. This will preserve the Styler styles (styler uses the querysting).
- On the CK Editor Browser configuration page select the browser view.
- Also, select the styler rule that you want applied to the browser view. E.g. an embed style that will remove the sidebars / breadcrumbs from the view since it will be in a dialog popup
- Finally, specify the wysiwyg button label text. This is the text that will be displayed when the button is hovered over.