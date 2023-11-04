import subprocess
from pathlib import Path

OUTPUT = Path('_site/')

def tree(path=OUTPUT):
    body = ''
    for f in sorted(path.iterdir()):
        if f.is_dir():
            body += '<li>' + f.stem + tree(f) + '</li>'
    for f in sorted(path.iterdir()):
        if f.is_file() and f.suffix == '.pdf':
            body += '<li><a href="' + str(f.relative_to(OUTPUT)) + '">' + f.stem + '</a></li>'
    return '<ul>' + body + '</ul>'

if __name__ == '__main__':
    OUTPUT.mkdir(parents=True, exist_ok=True)

    # generate pdfs
    for sch in Path().glob('**/*.kicad_sch'):
        if sch.stem != sch.parent.stem: # don't process subsheets
            continue
        out = OUTPUT / sch.parent.with_suffix('.pdf')
        out.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['kicad-cli', 'sch', 'export', 'pdf', sch, '-o', out], capture_output=True)
        print('processed', sch)

    # generate index.html as a sitemap
    with (OUTPUT / 'index.html').open('w') as idx:
        idx.write('<!DOCTYPE html><html><body>' + tree() + '</body></html>')
