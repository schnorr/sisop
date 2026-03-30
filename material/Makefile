all:
	echo "specify a target"

%.pdf: %.org
	emacs -batch $^ \
	--eval "(require 'ob-R)" \
	--funcall org-babel-tangle
	emacs -batch $^ \
	--eval "(require 'ob-R)" \
	--eval "(setq org-latex-listings 'minted org-latex-packages-alist '((\"\" \"minted\")) org-latex-pdf-process '(\"pdflatex -shell-escape -interaction nonstopmode -output-directory %o %f\" \"pdflatex -shell-escape -interaction nonstopmode -output-directory %o %f\"))" \
	--eval "(setq org-latex-minted-options '((\"frame\" \"lines\") (\"fontsize\" \"\\\\scriptsize\")))" \
	--funcall org-beamer-export-to-pdf

watch-%.pdf: %.org
	@echo "Watching $< for changes. Press Ctrl+C to stop."
	@while true; do \
		inotifywait -q -e close_write,modify "$<"; \
		echo "\nChange detected in $<, rebuilding $*.pdf..."; \
		rm -f "$*.pdf"; \
		$(MAKE) "$*.pdf"; \
	done
