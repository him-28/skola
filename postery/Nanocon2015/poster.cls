%%
%% This is file `a0poster.cls'
%%
%% Copyright (C) 07.05.97 Gerlinde Kettl and Matthias Weiser
%%
%% Problems, bugs and comments to
%% gerlinde.kettl@physik.uni-regensburg.de
%%
\ProvidesClass{poster}[2008/06/20 v0 poster class (GK, MW, DN)]
\NeedsTeXFormat{LaTeX2e}[1995/06/01]
\LoadClass{article}
\RequirePackage{color}
\RequirePackage{graphicx}
\RequirePackage{multicol}
\RequirePackage{a0size}

\newif\ifdraft

\DeclareOption{draft}{
\drafttrue
}
\DeclareOption{final}{
\draftfalse
}
\DeclareOption{classic}{
\definecolor{section}{rgb}{0.3,0.3,0.4}
\definecolor{subsection}{rgb}{0.4,0.4,0.5}
\definecolor{emph}{rgb}{0.65,0.3,0.3}
}
\DeclareOption{blues}{
\definecolor{section}{rgb}{0.137,0.275,0.392}
\definecolor{subsection}{rgb}{0.224,0.388,0.529}
\definecolor{emph}{rgb}{0.0,0.40,0.15}
}
\DeclareOption{green}{
\definecolor{section}{rgb}{0.04,0.27,0.3}
\definecolor{subsection}{rgb}{0.04,0.38,0.31}
\definecolor{emph}{rgb}{0.6,0.0,0.2}
}
\DeclareOption*{\PackageWarning{a0poster}{Unknown Option \CurrentOption}}
\ExecuteOptions{final,classic}
\ProcessOptions\relax

%% Setting proper dimensions for a DIN A0 printer

\setlength{\headheight}{0cm}
\setlength{\headsep}{0cm}
\setlength{\topmargin}{0cm}
\setlength{\oddsidemargin}{0cm}

\renewcommand{\tiny}{\fontsize{12}{14}\selectfont}
\renewcommand{\scriptsize}{\fontsize{14.4}{18}\selectfont}
\renewcommand{\footnotesize}{\fontsize{17.28}{22}\selectfont}
\renewcommand{\small}{\fontsize{20.74}{25}\selectfont}
%\renewcommand{\normalsize}{\fontsize{24.88}{30}\selectfont}
\renewcommand{\normalsize}{\fontsize{17.28}{22}\selectfont}
\renewcommand{\large}{\fontsize{29.86}{37}\selectfont}
\renewcommand{\Large}{\fontsize{35.83}{45}\selectfont}
\renewcommand{\LARGE}{\fontsize{43}{54}\selectfont}
\renewcommand{\huge}{\fontsize{51.6}{64}\selectfont}
\renewcommand{\Huge}{\fontsize{61.92}{77}\selectfont}
\newcommand{\veryHuge}{\fontsize{74.3}{93}\selectfont}
\newcommand{\VeryHuge}{\fontsize{89.16}{112}\selectfont}
\newcommand{\VERYHuge}{\fontsize{107}{134}\selectfont}

\setlength\smallskipamount{6pt plus 2pt minus 2pt}
\setlength\medskipamount{12pt plus 4pt minus 4pt}
\setlength\bigskipamount{24pt plus 8pt minus 8pt}

\setlength\abovecaptionskip{25pt}
\setlength\belowcaptionskip{0pt}
\setlength\abovedisplayskip{25pt plus 6pt minus 15 pt}
\setlength\abovedisplayshortskip{0pt plus 6pt}
\setlength\belowdisplayshortskip{13pt plus 7pt minus 6pt}
\setlength\belowdisplayskip\abovedisplayskip

\normalsize

\parindent=0pt
\parskip=0.6\baselineskip

\AtBeginDocument{\pagestyle{empty}}

\def\narrowerbox#1#2{\dimen0=\hsize \advance\dimen0 by -6pt%
  \vbox{\hsize=\dimen0#1\strut\leftskip=0.2em\rightskip=0.2em\relax#2}}

\def\section#1{\par\vskip15pt
  \colorbox{section}
           {\narrowerbox{\Large\sffamily\bfseries}{\color{white}#1}}%
  \par\nobreak}

\def\subsection#1{\par\vskip15pt
  \colorbox{subsection}
           {\narrowerbox{\sffamily\bfseries}{\color{white}#1}}%
  \par\nobreak}

\def\paragraph#1{\par\emph{#1.\quad}\ignorespaces}

\long\def\@makecaption#1{%
  \sbox\@tempboxa{\it#1}%
  \ifdim \wd\@tempboxa >\hsize
    \it#1\par
  \else
    \hb@xt@\hsize{\hfil\box\@tempboxa\hfil}%
  \fi}

\def\figure{\@ifnextchar[{\@figure}{\@figure[width=\columnwidth]}}
\def\@figure[#1]#2#3{%
  \noindent\vbox{\parskip=0pt
  \hfil\includegraphics[#1]{#2}%
  \def\@tmp{#3}%
  \ifx\@tmp\empty\else\par\medskip\@makecaption{#3}\fi}}
\def\xfigure#1#2{%
  \noindent\vbox{\parskip=0pt
  #1
  \def\@tmp{#2}%
  \ifx\@tmp\empty\else\par\medskip\@makecaption{#2}\fi}}

\def\title#1{
\begin{center}
\baselineskip=48pt
\textcolor{section}{\sffamily\bfseries\huge#1}
\end{center}
}

\def\narrowtitle#1{
\begin{center}
\hsize=\@authorboxwidth
\baselineskip=48pt
\textcolor{section}{\sffamily\bfseries\huge#1}
\end{center}
}

\long\def\authorbox#1#2{\vskip0.3ex\vbox{\hsize=\@authorboxwidth\relax
{\large\sc\color{section}\baselineskip=30pt\relax
#1
\par\vskip-0.8ex}
{\sl
#2}
}}

\long\def\affiliation#1#2{
\valign{##\vfil\cr
#1
\cr
\noalign{\hskip2cm}
#2
\cr}
\par\vskip0.6cm
}

\def\emph#1{\textcolor{emph}{\sffamily\bfseries #1}}
\def\ie{i.\,e.\ \ignorespaces}
\def\eg{e.\,g.\ \ignorespaces}
\def\fm#1{$^{#1}$}

\def\qarray#1{\vcenter{\tabskip\z@skip
  \everycr{\noalign{\smallskip}}%
  \vskip-\smallskipamount
  \halign{%
    \hfil$\displaystyle{##}$%
      &${}##{}$%
      &&$\displaystyle{##}$\hfil\cr
    #1\crcr}%
    \vskip-\smallskipamount}%
  }

\setlength{\columnsep}{1.2cm}
\setlength{\columnseprule}{0.5pt}

\endinput
%%
%% End of file `a0poster.cls'.
