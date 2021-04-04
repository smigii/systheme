#!/usr/bin/env bash

_systheme_completions(){

	local cur prev

	COMPREPLY=()

	if [ $COMP_CWORD -eq 1 ]; then

		COMPREPLY=($(compgen -W "$(ls ~/.config/systheme/themes)" "${COMP_WORDS[COMP_CWORD]}"))

	fi

}

complete -F _systheme_completions systheme
