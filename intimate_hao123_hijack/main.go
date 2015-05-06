package main

import (
	"fmt"
	"log"
	"net/http"
)

func intimate_hijack(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("path=%s, host=%s\n", r.URL.Path, r.Host)
	http.Redirect(w, r, "http://www.hao123.com/?tn=99223597_hao_pg&tt=12034&t=1430141166458", http.StatusFound)
	w.Write([]byte("abc"))
}

func main() {
	http.HandleFunc("/", intimate_hijack)
	err := http.ListenAndServe(":80", nil)
	if err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}
