# Jupyter core packages...
#IPython          : 8.14.0
#ipykernel        : 6.24.0
#ipywidgets       : 7.6.3
#jupyter_client   : 8.3.0
#jupyter_core     : 5.3.1
#jupyter_server   : 2.7.0
#jupyterlab       : 4.0.3
#nbclient         : 0.5.3
#nbconvert        : 7.7.2
#nbformat         : 5.9.1
#notebook         : 6.4.3
#qtconsole        : 5.1.0
#traitlets        : 5.9.0
"""
Error:
Variable inspector in jupyter show only integers. When variable set as string,
variable inspector is freeze. 

Solution: add else statment in _getcontentof function 
"""
def _getcontentof(x):
    length = 150
    if type(x).__name__ == 'DataFrame':
        colnames = ', '.join(x.columns.map(str))
        content = "Column names: %s" % colnames
    elif type(x).__name__ == 'Series':
        content = "Series [%d rows]" % x.shape
    elif type(x).__name__ == 'ndarray':
        content = x.__repr__()
    else:
        if hasattr(x, '__len__'):
            if len(x) > length:
                content = str(x[:length])
            #------------------------------------
            # Add this string if Variable inspector window  is freeze:
            else:
                content = str(x[:length])
        else:
            content = str(x)
        if len(content) > 150:
            return content[:150] + " ..."
    return content
