# ipp-rename

`ipp-rename` is a command-line tool to rename jobs in IPP control files.

Firefox (Iceweasel) use the page title as the IPP job name but does not trim it to 255 chars (Maximum length of this attribute according to [RFC2911](http://tools.ietf.org/html/rfc2911).  Our printer silently rejected these jobs, making CUPS print queue stale.

## Usage

You'd rather stop CUPS before toying with a job it is processing…  Then simply run `ipp-rename` with the IPP control files to edit as arguments (these files are usualy found in `/var/spool/cups/`):

```
# ipp-rename c00035
job c00035 title is: "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
remame job [yN] y
New job name: A shorter more decent name
```
