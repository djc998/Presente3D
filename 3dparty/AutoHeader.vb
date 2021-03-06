Imports EnvDTE

Imports System.Diagnostics

Public Module AutoHeader

    '------------------------------------------------------------------------------

    'FILE DESCRIPTION: My personal text macros

    '------------------------------------------------------------------------------

    Sub InsertFileHandler()

        ' DESCRIPTION: Add file description

        'Detect file type:

        Dim DocName

        Dim DocNameLen

        Dim DotChar

        Dim DotPos

        Dim DocExt

        Dim DocBase

        Dim HeaderChar

        DocName = ActiveDocument.Name

        DocNameLen = Len(DocName)

        DotChar = "."

        DotPos = InStrRev(DocName, DotChar, -1, 0)



        DocBase = Left(DocName, DotPos - 1)

        DocExt = Right(DocName, Len(DocName) - DotPos)

        HeaderChar = "h"

        If StrComp(DocExt, HeaderChar, 1) = 0 Then

            ' Header

            DTE.ActiveDocument.Selection.StartOfDocument()

            DTE.ActiveDocument.Selection.Text = "#ifndef " + DocBase + "_header"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "#define " + DocBase + "_header"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "/* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* File: " + DocName + " "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* Created by: Vitaly V. Boiko"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* Short Description: "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "*/"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.EndOfDocument()

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "#endif /* " + DocBase + "_header */"

            DTE.ActiveDocument.Selection.NewLine()

        Else

            ' Cpp

            DTE.ActiveDocument.Selection.StartOfDocument()

            DTE.ActiveDocument.Selection.Text = "/* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = " * File: " + DocName + " "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* Company: Pixela "

            DTE.ActiveDocument.Selection.NewLine()



            DTE.ActiveDocument.Selection.Text = "* Creation Date: " + CStr(Date.Today()) + ""

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* Created by: Vitalii V. Boiko"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* e-mail: vitalymeister@gmail.com"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* Description: "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* History: "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "* "

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "*/"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "#include " + Chr(34) + "stdafx.h" + Chr(34)

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "#include " + Chr(34) + DocBase + ".h" + Chr(34)

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.NewLine()



        End If

    End Sub



    Sub InsertBaseClassHandler()

        ' DESCRIPTION: Add file description

        'Detect file type:

        Dim DocName

        Dim DocNameLen

        Dim DotChar

        Dim DotPos

        Dim DocExt

        Dim DocBase

        Dim HeaderChar

        DocName = ActiveDocument.Name

        DocNameLen = Len(DocName)

        DotChar = "."

        DotPos = InStrRev(DocName, DotChar, -1, 0)



        DocBase = Left(DocName, DotPos - 1)

        DocExt = Right(DocName, Len(DocName) - DotPos)





        HeaderChar = "h"

        If StrComp(DocExt, HeaderChar, 1) = 0 Then

            ' Header

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "class " + DocBase + ": public fUnknown{"

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.NewLine()

            DTE.ActiveDocument.Selection.Text = "};"

            DTE.ActiveDocument.Selection.NewLine()

        Else

            DTE.ActiveDocument.Selection.Text = "void " + DocBase + "::"

        End If

    End Sub



End Module
