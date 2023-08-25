document.addEventListener("DOMContentLoaded", function () {
    const generateForm = document.getElementById("generate-form");
    const generatedPassword = document.getElementById("generated-password");

    generateForm.addEventListener("submit", function (event) {
        event.preventDefault();

        const username = document.getElementById("username").value;
        generatedPassword.textContent = "Generating...";

        fetch("/generate", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({ username: username }),
        })
            .then((response) => response.text())
            .then((data) => {
                generatedPassword.textContent = `Generated Password: ${data}`;
            })
            .catch((error) => {
                console.error("Error:", error);
                generatedPassword.textContent = "Error generating password.";
            });
    });
});
